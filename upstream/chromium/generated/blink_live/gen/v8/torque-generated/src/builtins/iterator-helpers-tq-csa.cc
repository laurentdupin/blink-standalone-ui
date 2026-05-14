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
#include "torque-generated/src/builtins/iterator-helpers-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/growable-fixed-array-tq-csa.h"
#include "torque-generated/src/builtins/iterator-tq-csa.h"
#include "torque-generated/src/builtins/iterator-from-tq-csa.h"
#include "torque-generated/src/builtins/iterator-helpers-tq-csa.h"
#include "torque-generated/src/builtins/reflect-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/src/objects/js-iterator-helpers-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/property-descriptor-object-tq-csa.h"
#include "torque-generated/test/torque/test-torque-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=9&c=1
TNode<BoolT> IsIteratorHelperExhausted_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp0});
    tmp2 = FromConstexpr_JSIteratorHelperState_constexpr_kCompleted_0(state_, JSIteratorHelperState::kCompleted);
    tmp3 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp2});
    tmp4 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp1}, TNode<Smi>{tmp3});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BoolT>{tmp4};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=14&c=1
void MarkIteratorHelperAsExhausted_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Smi> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = FromConstexpr_JSIteratorHelperState_constexpr_kCompleted_0(state_, JSIteratorHelperState::kCompleted);
    tmp2 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp1});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp0}, tmp2);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=19&c=1
TNode<BoolT> IsIteratorHelperExecuting_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp0});
    tmp2 = FromConstexpr_JSIteratorHelperState_constexpr_kExecuting_0(state_, JSIteratorHelperState::kExecuting);
    tmp3 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp2});
    tmp4 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp1}, TNode<Smi>{tmp3});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BoolT>{tmp4};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=27&c=1
void ThrowIfIteratorHelperExecuting_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = IsIteratorHelperExecuting_0(state_, TNode<JSIteratorHelper>{p_helper});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kGeneratorRunning));
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=34&c=1
void MarkIteratorHelperAsExecuting_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = IsIteratorHelperExecuting_0(state_, TNode<JSIteratorHelper>{p_helper});
    tmp1 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 35});
      CodeStubAssembler(state_).FailAssert("Torque assert '!IsIteratorHelperExecuting(helper)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Smi> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp3 = FromConstexpr_JSIteratorHelperState_constexpr_kExecuting_0(state_, JSIteratorHelperState::kExecuting);
    tmp4 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp3});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp2}, tmp4);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=40&c=1
TNode<BoolT> IteratorHelperIsSuspendedStart_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp0});
    tmp2 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp3 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp2});
    tmp4 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp1}, TNode<Smi>{tmp3});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BoolT>{tmp4};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=45&c=1
void MarkIteratorHelperAsFinishedExecuting_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = IsIteratorHelperExecuting_0(state_, TNode<JSIteratorHelper>{p_helper});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 46});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsIteratorHelperExecuting(helper)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Smi> tmp3;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp2 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedYield_0(state_, JSIteratorHelperState::kSuspendedYield);
    tmp3 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp2});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp1}, tmp3);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=52&c=1
TorqueStructIteratorRecord GetIteratorDirect_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_obj) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  TNode<JSAny> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kNextString_0(state_);
    tmp1 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<JSAny>{p_obj}, TNode<JSAny>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructIteratorRecord{TNode<JSReceiver>{p_obj}, TNode<JSAny>{tmp1}};
}

TF_BUILTIN(IteratorHelperPrototypeNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSIteratorHelper> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSIteratorHelper_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  TNode<Object> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_Object_constexpr_string_0(state_, "Iterator Helper.prototype.next");
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIncompatibleMethodReceiver), TNode<Object>{tmp2}, TNode<Object>{parameter1});
  }

  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    ThrowIfIteratorHelperExecuting_0(state_, TNode<Context>{parameter0}, TNode<JSIteratorHelper>{tmp0});
    tmp3 = IsIteratorHelperExhausted_0(state_, TNode<JSIteratorHelper>{tmp0});
    ca_.Branch(tmp3, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp4;
  TNode<True> tmp5;
  TNode<JSObject> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = Undefined_0(state_);
    tmp5 = True_0(state_);
    tmp6 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp4}, TNode<Boolean>{tmp5});
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<JSIteratorMapHelper> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = Cast_JSIteratorMapHelper_0(state_, TNode<HeapObject>{tmp0}, &label8);
    ca_.Goto(&block9);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block10);
    }
  }

  TNode<JSIteratorFilterHelper> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = Cast_JSIteratorFilterHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label10);
    ca_.Goto(&block13);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block14);
    }
  }

  TNode<JSAny> tmp11;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp11 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorMapHelperNext, parameter0, tmp7);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<JSIteratorTakeHelper> tmp12;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = Cast_JSIteratorTakeHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label13);
    ca_.Goto(&block17);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block18);
    }
  }

  TNode<JSAny> tmp14;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp14 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorFilterHelperNext, parameter0, tmp9);
    CodeStubAssembler(state_).Return(tmp14);
  }

  TNode<JSIteratorDropHelper> tmp15;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    compiler::CodeAssemblerLabel label16(&ca_);
    tmp15 = Cast_JSIteratorDropHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label16);
    ca_.Goto(&block21);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block22);
    }
  }

  TNode<JSAny> tmp17;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp17 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorTakeHelperNext, parameter0, tmp12);
    CodeStubAssembler(state_).Return(tmp17);
  }

  TNode<JSIteratorFlatMapHelper> tmp18;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    compiler::CodeAssemblerLabel label19(&ca_);
    tmp18 = Cast_JSIteratorFlatMapHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label19);
    ca_.Goto(&block25);
    if (label19.is_used()) {
      ca_.Bind(&label19);
      ca_.Goto(&block26);
    }
  }

  TNode<JSAny> tmp20;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp20 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorDropHelperNext, parameter0, tmp15);
    CodeStubAssembler(state_).Return(tmp20);
  }

  TNode<JSIteratorConcatHelper> tmp21;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    compiler::CodeAssemblerLabel label22(&ca_);
    tmp21 = Cast_JSIteratorConcatHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label22);
    ca_.Goto(&block29);
    if (label22.is_used()) {
      ca_.Bind(&label22);
      ca_.Goto(&block30);
    }
  }

  TNode<JSAny> tmp23;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp23 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorFlatMapHelperNext, parameter0, tmp18);
    CodeStubAssembler(state_).Return(tmp23);
  }

  TNode<JSIteratorZipKeyedHelper> tmp24;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    compiler::CodeAssemblerLabel label25(&ca_);
    tmp24 = Cast_JSIteratorZipKeyedHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label25);
    ca_.Goto(&block33);
    if (label25.is_used()) {
      ca_.Bind(&label25);
      ca_.Goto(&block34);
    }
  }

  TNode<JSAny> tmp26;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp26 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorConcatHelperNext, parameter0, tmp21);
    CodeStubAssembler(state_).Return(tmp26);
  }

  TNode<JSIteratorZipHelper> tmp27;
  if (block34.is_used()) {
    ca_.Bind(&block34);
    compiler::CodeAssemblerLabel label28(&ca_);
    tmp27 = Cast_JSIteratorZipHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label28);
    ca_.Goto(&block37);
    if (label28.is_used()) {
      ca_.Bind(&label28);
      ca_.Goto(&block38);
    }
  }

  TNode<JSAny> tmp29;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp29 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorZipKeyedHelperNext, parameter0, tmp24);
    CodeStubAssembler(state_).Return(tmp29);
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:108:7");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> tmp30;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp30 = ca_.CallBuiltin<JSAny>(Builtin::kIteratorZipHelperNext, parameter0, tmp27);
    CodeStubAssembler(state_).Return(tmp30);
  }
}

TF_BUILTIN(IteratorHelperPrototypeReturn, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block47(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block52(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block53(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block54(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block55(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block56(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block61(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block62(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block63(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSIteratorHelper> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSIteratorHelper_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  TNode<Object> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_Object_constexpr_string_0(state_, "Iterator Helper.prototype.return");
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIncompatibleMethodReceiver), TNode<Object>{tmp2}, TNode<Object>{parameter1});
  }

  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    ThrowIfIteratorHelperExecuting_0(state_, TNode<Context>{parameter0}, TNode<JSIteratorHelper>{tmp0});
    tmp3 = IsIteratorHelperExhausted_0(state_, TNode<JSIteratorHelper>{tmp0});
    ca_.Branch(tmp3, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp4;
  TNode<True> tmp5;
  TNode<JSObject> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = Undefined_0(state_);
    tmp5 = True_0(state_);
    tmp6 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp4}, TNode<Boolean>{tmp5});
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<BoolT> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = IteratorHelperIsSuspendedStart_0(state_, TNode<JSIteratorHelper>{tmp0});
    ca_.Branch(tmp7, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<JSIteratorConcatHelper> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{tmp0});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_JSIteratorConcatHelper_0(state_, TNode<HeapObject>{tmp0}, &label9);
    ca_.Goto(&block11);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block12);
    }
  }

  TNode<JSIteratorHelperSimple> tmp10;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_JSIteratorHelperSimple_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label11);
    ca_.Goto(&block15);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block16);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block9);
  }

  TNode<JSIteratorZipHelper> tmp12;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = Cast_JSIteratorZipHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label13);
    ca_.Goto(&block25);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block26);
    }
  }

  TNode<IntPtrT> tmp14;
      TNode<JSAny> tmp16;
  TNode<JSReceiver> tmp17;
  TNode<IntPtrT> tmp18;
      TNode<JSAny> tmp20;
  TNode<IntPtrT> tmp21;
      TNode<JSAny> tmp23;
  TNode<JSAny> tmp24;
      TNode<JSAny> tmp26;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block19);
      ca_.Bind(&catch15_skip);
    }
    tmp17 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp10, tmp14});
    compiler::CodeAssemblerExceptionHandlerLabel catch19__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch19__label);
    tmp18 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch19__label.is_used()) {
      compiler::CodeAssemblerLabel catch19_skip(&ca_);
      ca_.Goto(&catch19_skip);
      ca_.Bind(&catch19__label, &tmp20);
      ca_.Goto(&block20);
      ca_.Bind(&catch19_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch22__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch22__label);
    tmp21 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp18});
    }
    if (catch22__label.is_used()) {
      compiler::CodeAssemblerLabel catch22_skip(&ca_);
      ca_.Goto(&catch22_skip);
      ca_.Bind(&catch22__label, &tmp23);
      ca_.Goto(&block21);
      ca_.Bind(&catch22_skip);
    }
    tmp24 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp10, tmp21});
    compiler::CodeAssemblerExceptionHandlerLabel catch25__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch25__label);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp17}, TNode<JSAny>{tmp24}});
    }
    if (catch25__label.is_used()) {
      compiler::CodeAssemblerLabel catch25_skip(&ca_);
      ca_.Goto(&catch25_skip);
      ca_.Bind(&catch25__label, &tmp26);
      ca_.Goto(&block22);
      ca_.Bind(&catch25_skip);
    }
    ca_.Goto(&block13);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp27;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp27 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp16, tmp27);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp28;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp28 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp20, tmp28);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp29;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp29 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp23, tmp29);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp30;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp30 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp26, tmp30);
  }

  TNode<JSAny> phi_bb18_5;
  TNode<Union<JSMessageObject, TheHole>> phi_bb18_6;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_5, &phi_bb18_6);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb18_5, phi_bb18_6);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:158:9");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp31;
  TNode<FixedArray> tmp32;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp32 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp12, tmp31});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp32}, true);
    ca_.Goto(&block13);
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block9);
  }

  TNode<Undefined> tmp33;
  TNode<True> tmp34;
  TNode<JSObject> tmp35;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp33 = Undefined_0(state_);
    tmp34 = True_0(state_);
    tmp35 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp33}, TNode<Boolean>{tmp34});
    CodeStubAssembler(state_).Return(tmp35);
  }

  TNode<JSIteratorFlatMapHelper> tmp36;
      TNode<JSAny> tmp39;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{tmp0});
    compiler::CodeAssemblerLabel label37(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch38__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch38__label);
    tmp36 = Cast_JSIteratorFlatMapHelper_0(state_, TNode<HeapObject>{tmp0}, &label37);
    }
    if (catch38__label.is_used()) {
      compiler::CodeAssemblerLabel catch38_skip(&ca_);
      ca_.Goto(&catch38_skip);
      ca_.Bind(&catch38__label, &tmp39);
      ca_.Goto(&block33);
      ca_.Bind(&catch38_skip);
    }
    ca_.Goto(&block31);
    if (label37.is_used()) {
      ca_.Bind(&label37);
      ca_.Goto(&block32);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp40;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp40 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp39, tmp40);
  }

  TNode<JSIteratorHelperSimple> tmp41;
      TNode<JSAny> tmp44;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    compiler::CodeAssemblerLabel label42(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch43__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch43__label);
    tmp41 = Cast_JSIteratorHelperSimple_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label42);
    }
    if (catch43__label.is_used()) {
      compiler::CodeAssemblerLabel catch43_skip(&ca_);
      ca_.Goto(&catch43_skip);
      ca_.Bind(&catch43__label, &tmp44);
      ca_.Goto(&block52);
      ca_.Bind(&catch43_skip);
    }
    ca_.Goto(&block50);
    if (label42.is_used()) {
      ca_.Bind(&label42);
      ca_.Goto(&block51);
    }
  }

  TNode<IntPtrT> tmp45;
      TNode<JSAny> tmp47;
  TNode<JSReceiver> tmp48;
  TNode<IntPtrT> tmp49;
      TNode<JSAny> tmp51;
  TNode<IntPtrT> tmp52;
      TNode<JSAny> tmp54;
  TNode<JSAny> tmp55;
      TNode<JSAny> tmp57;
  TNode<IntPtrT> tmp58;
      TNode<JSAny> tmp60;
  TNode<JSReceiver> tmp61;
  TNode<IntPtrT> tmp62;
      TNode<JSAny> tmp64;
  TNode<IntPtrT> tmp65;
      TNode<JSAny> tmp67;
  TNode<JSAny> tmp68;
      TNode<JSAny> tmp70;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    compiler::CodeAssemblerExceptionHandlerLabel catch46__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch46__label);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    }
    if (catch46__label.is_used()) {
      compiler::CodeAssemblerLabel catch46_skip(&ca_);
      ca_.Goto(&catch46_skip);
      ca_.Bind(&catch46__label, &tmp47);
      ca_.Goto(&block36);
      ca_.Bind(&catch46_skip);
    }
    tmp48 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp36, tmp45});
    compiler::CodeAssemblerExceptionHandlerLabel catch50__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch50__label);
    tmp49 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch50__label.is_used()) {
      compiler::CodeAssemblerLabel catch50_skip(&ca_);
      ca_.Goto(&catch50_skip);
      ca_.Bind(&catch50__label, &tmp51);
      ca_.Goto(&block37);
      ca_.Bind(&catch50_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch53__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch53__label);
    tmp52 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp45}, TNode<IntPtrT>{tmp49});
    }
    if (catch53__label.is_used()) {
      compiler::CodeAssemblerLabel catch53_skip(&ca_);
      ca_.Goto(&catch53_skip);
      ca_.Bind(&catch53__label, &tmp54);
      ca_.Goto(&block38);
      ca_.Bind(&catch53_skip);
    }
    tmp55 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp36, tmp52});
    compiler::CodeAssemblerExceptionHandlerLabel catch56__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch56__label);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp48}, TNode<JSAny>{tmp55}});
    }
    if (catch56__label.is_used()) {
      compiler::CodeAssemblerLabel catch56_skip(&ca_);
      ca_.Goto(&catch56_skip);
      ca_.Bind(&catch56__label, &tmp57);
      ca_.Goto(&block39);
      ca_.Bind(&catch56_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch59__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch59__label);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch59__label.is_used()) {
      compiler::CodeAssemblerLabel catch59_skip(&ca_);
      ca_.Goto(&catch59_skip);
      ca_.Bind(&catch59__label, &tmp60);
      ca_.Goto(&block44);
      ca_.Bind(&catch59_skip);
    }
    tmp61 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp36, tmp58});
    compiler::CodeAssemblerExceptionHandlerLabel catch63__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch63__label);
    tmp62 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch63__label.is_used()) {
      compiler::CodeAssemblerLabel catch63_skip(&ca_);
      ca_.Goto(&catch63_skip);
      ca_.Bind(&catch63__label, &tmp64);
      ca_.Goto(&block45);
      ca_.Bind(&catch63_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch66__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch66__label);
    tmp65 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp58}, TNode<IntPtrT>{tmp62});
    }
    if (catch66__label.is_used()) {
      compiler::CodeAssemblerLabel catch66_skip(&ca_);
      ca_.Goto(&catch66_skip);
      ca_.Bind(&catch66__label, &tmp67);
      ca_.Goto(&block46);
      ca_.Bind(&catch66_skip);
    }
    tmp68 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp36, tmp65});
    compiler::CodeAssemblerExceptionHandlerLabel catch69__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch69__label);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp61}, TNode<JSAny>{tmp68}});
    }
    if (catch69__label.is_used()) {
      compiler::CodeAssemblerLabel catch69_skip(&ca_);
      ca_.Goto(&catch69_skip);
      ca_.Bind(&catch69__label, &tmp70);
      ca_.Goto(&block47);
      ca_.Bind(&catch69_skip);
    }
    ca_.Goto(&block29);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp71;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp71 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block35, tmp47, tmp71);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp72;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp72 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block35, tmp51, tmp72);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp73;
  if (block38.is_used()) {
    ca_.Bind(&block38);
    tmp73 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block35, tmp54, tmp73);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp74;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp74 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block35, tmp57, tmp74);
  }

  TNode<JSAny> phi_bb35_5;
  TNode<Union<JSMessageObject, TheHole>> phi_bb35_6;
  TNode<IntPtrT> tmp75;
      TNode<JSAny> tmp77;
  TNode<JSReceiver> tmp78;
      TNode<JSAny> tmp80;
      TNode<JSAny> tmp82;
      TNode<JSAny> tmp84;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_5, &phi_bb35_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch76__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch76__label);
    tmp75 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch76__label.is_used()) {
      compiler::CodeAssemblerLabel catch76_skip(&ca_);
      ca_.Goto(&catch76_skip);
      ca_.Bind(&catch76__label, &tmp77);
      ca_.Goto(&block40);
      ca_.Bind(&catch76_skip);
    }
    tmp78 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp36, tmp75});
    compiler::CodeAssemblerExceptionHandlerLabel catch79__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch79__label);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp78});
    }
    if (catch79__label.is_used()) {
      compiler::CodeAssemblerLabel catch79_skip(&ca_);
      ca_.Goto(&catch79_skip);
      ca_.Bind(&catch79__label, &tmp80);
      ca_.Goto(&block41);
      ca_.Bind(&catch79_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch81__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch81__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{tmp36});
    }
    if (catch81__label.is_used()) {
      compiler::CodeAssemblerLabel catch81_skip(&ca_);
      ca_.Goto(&catch81_skip);
      ca_.Bind(&catch81__label, &tmp82);
      ca_.Goto(&block42);
      ca_.Bind(&catch81_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch83__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch83__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb35_5, phi_bb35_6);
    CodeStubAssembler(state_).Unreachable();
    }
    if (catch83__label.is_used()) {
      compiler::CodeAssemblerLabel catch83_skip(&ca_);
      ca_.Bind(&catch83__label, &tmp84);
      ca_.Goto(&block43);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp85;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp85 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp77, tmp85);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp86;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    tmp86 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp80, tmp86);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp87;
  if (block42.is_used()) {
    ca_.Bind(&block42);
    tmp87 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp82, tmp87);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp88;
  if (block43.is_used()) {
    ca_.Bind(&block43);
    tmp88 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp84, tmp88);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp89;
  if (block44.is_used()) {
    ca_.Bind(&block44);
    tmp89 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp60, tmp89);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp90;
  if (block45.is_used()) {
    ca_.Bind(&block45);
    tmp90 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp64, tmp90);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp91;
  if (block46.is_used()) {
    ca_.Bind(&block46);
    tmp91 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp67, tmp91);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp92;
  if (block47.is_used()) {
    ca_.Bind(&block47);
    tmp92 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp70, tmp92);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp93;
  if (block52.is_used()) {
    ca_.Bind(&block52);
    tmp93 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp44, tmp93);
  }

  TNode<JSIteratorZipHelper> tmp94;
      TNode<JSAny> tmp97;
  if (block51.is_used()) {
    ca_.Bind(&block51);
    compiler::CodeAssemblerLabel label95(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch96__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch96__label);
    tmp94 = Cast_JSIteratorZipHelper_0(state_, TNode<HeapObject>{ca_.UncheckedCast<JSIteratorHelper>(tmp0)}, &label95);
    }
    if (catch96__label.is_used()) {
      compiler::CodeAssemblerLabel catch96_skip(&ca_);
      ca_.Goto(&catch96_skip);
      ca_.Bind(&catch96__label, &tmp97);
      ca_.Goto(&block61);
      ca_.Bind(&catch96_skip);
    }
    ca_.Goto(&block59);
    if (label95.is_used()) {
      ca_.Bind(&label95);
      ca_.Goto(&block60);
    }
  }

  TNode<IntPtrT> tmp98;
      TNode<JSAny> tmp100;
  TNode<JSReceiver> tmp101;
  TNode<IntPtrT> tmp102;
      TNode<JSAny> tmp104;
  TNode<IntPtrT> tmp105;
      TNode<JSAny> tmp107;
  TNode<JSAny> tmp108;
      TNode<JSAny> tmp110;
  if (block50.is_used()) {
    ca_.Bind(&block50);
    compiler::CodeAssemblerExceptionHandlerLabel catch99__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch99__label);
    tmp98 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch99__label.is_used()) {
      compiler::CodeAssemblerLabel catch99_skip(&ca_);
      ca_.Goto(&catch99_skip);
      ca_.Bind(&catch99__label, &tmp100);
      ca_.Goto(&block53);
      ca_.Bind(&catch99_skip);
    }
    tmp101 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp41, tmp98});
    compiler::CodeAssemblerExceptionHandlerLabel catch103__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch103__label);
    tmp102 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch103__label.is_used()) {
      compiler::CodeAssemblerLabel catch103_skip(&ca_);
      ca_.Goto(&catch103_skip);
      ca_.Bind(&catch103__label, &tmp104);
      ca_.Goto(&block54);
      ca_.Bind(&catch103_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch106__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch106__label);
    tmp105 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp98}, TNode<IntPtrT>{tmp102});
    }
    if (catch106__label.is_used()) {
      compiler::CodeAssemblerLabel catch106_skip(&ca_);
      ca_.Goto(&catch106_skip);
      ca_.Bind(&catch106__label, &tmp107);
      ca_.Goto(&block55);
      ca_.Bind(&catch106_skip);
    }
    tmp108 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp41, tmp105});
    compiler::CodeAssemblerExceptionHandlerLabel catch109__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch109__label);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp101}, TNode<JSAny>{tmp108}});
    }
    if (catch109__label.is_used()) {
      compiler::CodeAssemblerLabel catch109_skip(&ca_);
      ca_.Goto(&catch109_skip);
      ca_.Bind(&catch109__label, &tmp110);
      ca_.Goto(&block56);
      ca_.Bind(&catch109_skip);
    }
    ca_.Goto(&block48);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp111;
  if (block53.is_used()) {
    ca_.Bind(&block53);
    tmp111 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp100, tmp111);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp112;
  if (block54.is_used()) {
    ca_.Bind(&block54);
    tmp112 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp104, tmp112);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp113;
  if (block55.is_used()) {
    ca_.Bind(&block55);
    tmp113 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp107, tmp113);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp114;
  if (block56.is_used()) {
    ca_.Bind(&block56);
    tmp114 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp110, tmp114);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp115;
  if (block61.is_used()) {
    ca_.Bind(&block61);
    tmp115 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp97, tmp115);
  }

  if (block60.is_used()) {
    ca_.Bind(&block60);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:196:9");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp116;
      TNode<JSAny> tmp118;
  TNode<FixedArray> tmp119;
      TNode<JSAny> tmp121;
  if (block59.is_used()) {
    ca_.Bind(&block59);
    compiler::CodeAssemblerExceptionHandlerLabel catch117__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch117__label);
    tmp116 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch117__label.is_used()) {
      compiler::CodeAssemblerLabel catch117_skip(&ca_);
      ca_.Goto(&catch117_skip);
      ca_.Bind(&catch117__label, &tmp118);
      ca_.Goto(&block62);
      ca_.Bind(&catch117_skip);
    }
    tmp119 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp94, tmp116});
    compiler::CodeAssemblerExceptionHandlerLabel catch120__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch120__label);
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp119}, true);
    }
    if (catch120__label.is_used()) {
      compiler::CodeAssemblerLabel catch120_skip(&ca_);
      ca_.Goto(&catch120_skip);
      ca_.Bind(&catch120__label, &tmp121);
      ca_.Goto(&block63);
      ca_.Bind(&catch120_skip);
    }
    ca_.Goto(&block48);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp122;
  if (block62.is_used()) {
    ca_.Bind(&block62);
    tmp122 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp118, tmp122);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp123;
  if (block63.is_used()) {
    ca_.Bind(&block63);
    tmp123 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block28, tmp121, tmp123);
  }

  if (block48.is_used()) {
    ca_.Bind(&block48);
    ca_.Goto(&block29);
  }

  TNode<Undefined> tmp124;
  TNode<True> tmp125;
  TNode<JSObject> tmp126;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{tmp0});
    tmp124 = Undefined_0(state_);
    tmp125 = True_0(state_);
    tmp126 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp124}, TNode<Boolean>{tmp125});
    CodeStubAssembler(state_).Return(tmp126);
  }

  TNode<JSAny> phi_bb28_3;
  TNode<Union<JSMessageObject, TheHole>> phi_bb28_4;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_3, &phi_bb28_4);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb28_3, phi_bb28_4);
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=210&c=1
TNode<JSIteratorMapHelper> NewJSIteratorMapHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_mapper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<FixedArray> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Uint32T> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Number> tmp21;
  TNode<JSIteratorMapHelper> tmp22;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ITERATOR_MAP_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = kEmptyFixedArray_0(state_);
    tmp5 = kEmptyFixedArray_0(state_);
    tmp6 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp7 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp6});
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp11 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp10}, TNode<Map>{tmp3}, TNode<BoolT>{tmp8}, TNode<BoolT>{tmp9});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp11, tmp12}, tmp3);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp11, tmp13}, tmp4);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp11, tmp14}, tmp5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp15}, tmp7);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp11, tmp16}, p_underlying.object);
    tmp17 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp17});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp11, tmp18}, p_underlying.next);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{tmp11, tmp19}, p_mapper);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp21 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp11, tmp20}, tmp21);
    tmp22 = TORQUE_CAST(TNode<HeapObject>{tmp11});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSIteratorMapHelper>{tmp22};
}

TF_BUILTIN(IteratorPrototypeMap, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kMapper);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.map");
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, parameter2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<JSIteratorMapHelper> tmp6;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = NewJSIteratorMapHelper_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>{tmp2});
    CodeStubAssembler(state_).Return(tmp6);
  }
}

TF_BUILTIN(IteratorMapHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorMapHelper> parameter1 = UncheckedParameter<JSIteratorMapHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Map> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<Number> tmp2;
  TNode<IntPtrT> tmp3;
      TNode<JSAny> tmp5;
  TNode<JSReceiver> tmp6;
  TNode<IntPtrT> tmp7;
      TNode<JSAny> tmp9;
  TNode<IntPtrT> tmp10;
      TNode<JSAny> tmp12;
  TNode<JSAny> tmp13;
  TNode<JSReceiver> tmp14;
      TNode<JSAny> tmp17;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp2 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{parameter1, tmp1});
    compiler::CodeAssemblerExceptionHandlerLabel catch4__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch4__label);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch4__label.is_used()) {
      compiler::CodeAssemblerLabel catch4_skip(&ca_);
      ca_.Goto(&catch4_skip);
      ca_.Bind(&catch4__label, &tmp5);
      ca_.Goto(&block5);
      ca_.Bind(&catch4_skip);
    }
    tmp6 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp3});
    compiler::CodeAssemblerExceptionHandlerLabel catch8__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch8__label);
    tmp7 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch8__label.is_used()) {
      compiler::CodeAssemblerLabel catch8_skip(&ca_);
      ca_.Goto(&catch8_skip);
      ca_.Bind(&catch8__label, &tmp9);
      ca_.Goto(&block6);
      ca_.Bind(&catch8_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch11__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch11__label);
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp7});
    }
    if (catch11__label.is_used()) {
      compiler::CodeAssemblerLabel catch11_skip(&ca_);
      ca_.Goto(&catch11_skip);
      ca_.Bind(&catch11__label, &tmp12);
      ca_.Goto(&block7);
      ca_.Bind(&catch11_skip);
    }
    tmp13 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp10});
    compiler::CodeAssemblerLabel label15(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch16__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch16__label);
    tmp14 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp6}, TNode<JSAny>{tmp13}}, TNode<Map>{tmp0}, &label15);
    }
    if (catch16__label.is_used()) {
      compiler::CodeAssemblerLabel catch16_skip(&ca_);
      ca_.Goto(&catch16_skip);
      ca_.Bind(&catch16__label, &tmp17);
      ca_.Goto(&block10);
      ca_.Bind(&catch16_skip);
    }
    ca_.Goto(&block8);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block9);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp18 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp5, tmp18);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp19;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp19 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp9, tmp19);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp20;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp20 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp12, tmp20);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp21;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp21 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp17, tmp21);
  }

      TNode<JSAny> tmp23;
  TNode<Undefined> tmp24;
  TNode<True> tmp25;
  TNode<JSObject> tmp26;
      TNode<JSAny> tmp28;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerExceptionHandlerLabel catch22__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch22__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch22__label.is_used()) {
      compiler::CodeAssemblerLabel catch22_skip(&ca_);
      ca_.Goto(&catch22_skip);
      ca_.Bind(&catch22__label, &tmp23);
      ca_.Goto(&block11);
      ca_.Bind(&catch22_skip);
    }
    tmp24 = Undefined_0(state_);
    tmp25 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch27__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch27__label);
    tmp26 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp24}, TNode<Boolean>{tmp25});
    }
    if (catch27__label.is_used()) {
      compiler::CodeAssemblerLabel catch27_skip(&ca_);
      ca_.Goto(&catch27_skip);
      ca_.Bind(&catch27__label, &tmp28);
      ca_.Goto(&block12);
      ca_.Bind(&catch27_skip);
    }
    CodeStubAssembler(state_).Return(tmp26);
  }

  TNode<JSAny> tmp29;
      TNode<JSAny> tmp31;
  TNode<IntPtrT> tmp32;
      TNode<JSAny> tmp34;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp35;
  TNode<Undefined> tmp36;
  TNode<JSAny> tmp37;
      TNode<JSAny> tmp39;
  TNode<IntPtrT> tmp40;
      TNode<JSAny> tmp42;
  TNode<Number> tmp43;
      TNode<JSAny> tmp45;
  TNode<Number> tmp46;
      TNode<JSAny> tmp48;
      TNode<JSAny> tmp50;
  TNode<False> tmp51;
  TNode<JSObject> tmp52;
      TNode<JSAny> tmp54;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    compiler::CodeAssemblerExceptionHandlerLabel catch30__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch30__label);
    tmp29 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp14}, TNode<Map>{tmp0});
    }
    if (catch30__label.is_used()) {
      compiler::CodeAssemblerLabel catch30_skip(&ca_);
      ca_.Goto(&catch30_skip);
      ca_.Bind(&catch30__label, &tmp31);
      ca_.Goto(&block13);
      ca_.Bind(&catch30_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch33__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch33__label);
    tmp32 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch33__label.is_used()) {
      compiler::CodeAssemblerLabel catch33_skip(&ca_);
      ca_.Goto(&catch33_skip);
      ca_.Bind(&catch33__label, &tmp34);
      ca_.Goto(&block16);
      ca_.Bind(&catch33_skip);
    }
    tmp35 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{parameter1, tmp32});
    tmp36 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch38__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch38__label);
    tmp37 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp35}, TNode<JSAny>{tmp36}, TNode<JSAny>{tmp29}, TNode<JSAny>{tmp2});
    }
    if (catch38__label.is_used()) {
      compiler::CodeAssemblerLabel catch38_skip(&ca_);
      ca_.Goto(&catch38_skip);
      ca_.Bind(&catch38__label, &tmp39);
      ca_.Goto(&block17);
      ca_.Bind(&catch38_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch41__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch41__label);
    tmp40 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch41__label.is_used()) {
      compiler::CodeAssemblerLabel catch41_skip(&ca_);
      ca_.Goto(&catch41_skip);
      ca_.Bind(&catch41__label, &tmp42);
      ca_.Goto(&block18);
      ca_.Bind(&catch41_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch44__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch44__label);
    tmp43 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch44__label.is_used()) {
      compiler::CodeAssemblerLabel catch44_skip(&ca_);
      ca_.Goto(&catch44_skip);
      ca_.Bind(&catch44__label, &tmp45);
      ca_.Goto(&block19);
      ca_.Bind(&catch44_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch47__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch47__label);
    tmp46 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp2}, TNode<Number>{tmp43});
    }
    if (catch47__label.is_used()) {
      compiler::CodeAssemblerLabel catch47_skip(&ca_);
      ca_.Goto(&catch47_skip);
      ca_.Bind(&catch47__label, &tmp48);
      ca_.Goto(&block20);
      ca_.Bind(&catch47_skip);
    }
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{parameter1, tmp40}, tmp46);
    compiler::CodeAssemblerExceptionHandlerLabel catch49__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch49__label);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch49__label.is_used()) {
      compiler::CodeAssemblerLabel catch49_skip(&ca_);
      ca_.Goto(&catch49_skip);
      ca_.Bind(&catch49__label, &tmp50);
      ca_.Goto(&block21);
      ca_.Bind(&catch49_skip);
    }
    tmp51 = False_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch53__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch53__label);
    tmp52 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp37}, TNode<Boolean>{tmp51});
    }
    if (catch53__label.is_used()) {
      compiler::CodeAssemblerLabel catch53_skip(&ca_);
      ca_.Goto(&catch53_skip);
      ca_.Bind(&catch53__label, &tmp54);
      ca_.Goto(&block22);
      ca_.Bind(&catch53_skip);
    }
    CodeStubAssembler(state_).Return(tmp52);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp55;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp55 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp23, tmp55);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp56;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp56 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp28, tmp56);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp57;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp57 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp31, tmp57);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp58;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp58 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp34, tmp58);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp59;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp59 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp39, tmp59);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp60;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp60 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp42, tmp60);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp61;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp61 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp45, tmp61);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp62;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp62 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp48, tmp62);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp63;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp63 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp50, tmp63);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp64;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp64 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block15, tmp54, tmp64);
  }

  TNode<JSAny> phi_bb15_6;
  TNode<Union<JSMessageObject, TheHole>> phi_bb15_7;
  TNode<IntPtrT> tmp65;
      TNode<JSAny> tmp67;
  TNode<JSReceiver> tmp68;
      TNode<JSAny> tmp70;
      TNode<JSAny> tmp72;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_6, &phi_bb15_7);
    compiler::CodeAssemblerExceptionHandlerLabel catch66__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch66__label);
    tmp65 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch66__label.is_used()) {
      compiler::CodeAssemblerLabel catch66_skip(&ca_);
      ca_.Goto(&catch66_skip);
      ca_.Bind(&catch66__label, &tmp67);
      ca_.Goto(&block23);
      ca_.Bind(&catch66_skip);
    }
    tmp68 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp65});
    compiler::CodeAssemblerExceptionHandlerLabel catch69__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch69__label);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp68});
    }
    if (catch69__label.is_used()) {
      compiler::CodeAssemblerLabel catch69_skip(&ca_);
      ca_.Goto(&catch69_skip);
      ca_.Bind(&catch69__label, &tmp70);
      ca_.Goto(&block24);
      ca_.Bind(&catch69_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch71__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch71__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb15_6, phi_bb15_7);
    CodeStubAssembler(state_).Unreachable();
    }
    if (catch71__label.is_used()) {
      compiler::CodeAssemblerLabel catch71_skip(&ca_);
      ca_.Bind(&catch71__label, &tmp72);
      ca_.Goto(&block25);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp73;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp73 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp67, tmp73);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp74;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp74 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp70, tmp74);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp75;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp75 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp72, tmp75);
  }

  TNode<JSAny> phi_bb2_4;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_5;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4, &phi_bb2_5);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb2_4, phi_bb2_5);
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=316&c=1
TNode<JSIteratorFilterHelper> NewJSIteratorFilterHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_predicate) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<FixedArray> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Uint32T> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Number> tmp21;
  TNode<JSIteratorFilterHelper> tmp22;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ITERATOR_FILTER_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = kEmptyFixedArray_0(state_);
    tmp5 = kEmptyFixedArray_0(state_);
    tmp6 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp7 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp6});
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp11 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp10}, TNode<Map>{tmp3}, TNode<BoolT>{tmp8}, TNode<BoolT>{tmp9});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp11, tmp12}, tmp3);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp11, tmp13}, tmp4);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp11, tmp14}, tmp5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp15}, tmp7);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp11, tmp16}, p_underlying.object);
    tmp17 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp17});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp11, tmp18}, p_underlying.next);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{tmp11, tmp19}, p_predicate);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp21 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp11, tmp20}, tmp21);
    tmp22 = TORQUE_CAST(TNode<HeapObject>{tmp11});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSIteratorFilterHelper>{tmp22};
}

TF_BUILTIN(IteratorPrototypeFilter, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kPredicate);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.filter");
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, parameter2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<JSIteratorFilterHelper> tmp6;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = NewJSIteratorFilterHelper_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>{tmp2});
    CodeStubAssembler(state_).Return(tmp6);
  }
}

TF_BUILTIN(IteratorFilterHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorFilterHelper> parameter1 = UncheckedParameter<JSIteratorFilterHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Map> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    ca_.Goto(&block5);
  }

  TNode<BoolT> tmp1;
      TNode<JSAny> tmp3;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerExceptionHandlerLabel catch2__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch2__label);
    tmp1 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch2__label.is_used()) {
      compiler::CodeAssemblerLabel catch2_skip(&ca_);
      ca_.Goto(&catch2_skip);
      ca_.Bind(&catch2__label, &tmp3);
      ca_.Goto(&block6);
      ca_.Bind(&catch2_skip);
    }
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp4;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp3, tmp4);
  }

  TNode<IntPtrT> tmp5;
      TNode<JSAny> tmp7;
  TNode<Number> tmp8;
  TNode<IntPtrT> tmp9;
      TNode<JSAny> tmp11;
  TNode<JSReceiver> tmp12;
  TNode<IntPtrT> tmp13;
      TNode<JSAny> tmp15;
  TNode<IntPtrT> tmp16;
      TNode<JSAny> tmp18;
  TNode<JSAny> tmp19;
  TNode<JSReceiver> tmp20;
      TNode<JSAny> tmp23;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerExceptionHandlerLabel catch6__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch6__label);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch6__label.is_used()) {
      compiler::CodeAssemblerLabel catch6_skip(&ca_);
      ca_.Goto(&catch6_skip);
      ca_.Bind(&catch6__label, &tmp7);
      ca_.Goto(&block7);
      ca_.Bind(&catch6_skip);
    }
    tmp8 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{parameter1, tmp5});
    compiler::CodeAssemblerExceptionHandlerLabel catch10__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch10__label);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch10__label.is_used()) {
      compiler::CodeAssemblerLabel catch10_skip(&ca_);
      ca_.Goto(&catch10_skip);
      ca_.Bind(&catch10__label, &tmp11);
      ca_.Goto(&block10);
      ca_.Bind(&catch10_skip);
    }
    tmp12 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp9});
    compiler::CodeAssemblerExceptionHandlerLabel catch14__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch14__label);
    tmp13 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch14__label.is_used()) {
      compiler::CodeAssemblerLabel catch14_skip(&ca_);
      ca_.Goto(&catch14_skip);
      ca_.Bind(&catch14__label, &tmp15);
      ca_.Goto(&block11);
      ca_.Bind(&catch14_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch17__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch17__label);
    tmp16 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp13});
    }
    if (catch17__label.is_used()) {
      compiler::CodeAssemblerLabel catch17_skip(&ca_);
      ca_.Goto(&catch17_skip);
      ca_.Bind(&catch17__label, &tmp18);
      ca_.Goto(&block12);
      ca_.Bind(&catch17_skip);
    }
    tmp19 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp16});
    compiler::CodeAssemblerLabel label21(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch22__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch22__label);
    tmp20 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp12}, TNode<JSAny>{tmp19}}, TNode<Map>{tmp0}, &label21);
    }
    if (catch22__label.is_used()) {
      compiler::CodeAssemblerLabel catch22_skip(&ca_);
      ca_.Goto(&catch22_skip);
      ca_.Bind(&catch22__label, &tmp23);
      ca_.Goto(&block15);
      ca_.Bind(&catch22_skip);
    }
    ca_.Goto(&block13);
    if (label21.is_used()) {
      ca_.Bind(&label21);
      ca_.Goto(&block14);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp24;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp24 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp7, tmp24);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp25;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp25 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp11, tmp25);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp26;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp26 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp15, tmp26);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp27;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp27 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp18, tmp27);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp28;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp28 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp23, tmp28);
  }

      TNode<JSAny> tmp30;
  TNode<Undefined> tmp31;
  TNode<True> tmp32;
  TNode<JSObject> tmp33;
      TNode<JSAny> tmp35;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    compiler::CodeAssemblerExceptionHandlerLabel catch29__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch29__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch29__label.is_used()) {
      compiler::CodeAssemblerLabel catch29_skip(&ca_);
      ca_.Goto(&catch29_skip);
      ca_.Bind(&catch29__label, &tmp30);
      ca_.Goto(&block16);
      ca_.Bind(&catch29_skip);
    }
    tmp31 = Undefined_0(state_);
    tmp32 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch34__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch34__label);
    tmp33 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp31}, TNode<Boolean>{tmp32});
    }
    if (catch34__label.is_used()) {
      compiler::CodeAssemblerLabel catch34_skip(&ca_);
      ca_.Goto(&catch34_skip);
      ca_.Bind(&catch34__label, &tmp35);
      ca_.Goto(&block17);
      ca_.Bind(&catch34_skip);
    }
    CodeStubAssembler(state_).Return(tmp33);
  }

  TNode<JSAny> tmp36;
      TNode<JSAny> tmp38;
  TNode<IntPtrT> tmp39;
      TNode<JSAny> tmp41;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp42;
  TNode<Undefined> tmp43;
  TNode<JSAny> tmp44;
      TNode<JSAny> tmp46;
  TNode<IntPtrT> tmp47;
      TNode<JSAny> tmp49;
  TNode<Number> tmp50;
      TNode<JSAny> tmp52;
  TNode<Number> tmp53;
      TNode<JSAny> tmp55;
  TNode<BoolT> tmp56;
      TNode<JSAny> tmp58;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    compiler::CodeAssemblerExceptionHandlerLabel catch37__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch37__label);
    tmp36 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp20}, TNode<Map>{tmp0});
    }
    if (catch37__label.is_used()) {
      compiler::CodeAssemblerLabel catch37_skip(&ca_);
      ca_.Goto(&catch37_skip);
      ca_.Bind(&catch37__label, &tmp38);
      ca_.Goto(&block18);
      ca_.Bind(&catch37_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch40__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch40__label);
    tmp39 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch40__label.is_used()) {
      compiler::CodeAssemblerLabel catch40_skip(&ca_);
      ca_.Goto(&catch40_skip);
      ca_.Bind(&catch40__label, &tmp41);
      ca_.Goto(&block21);
      ca_.Bind(&catch40_skip);
    }
    tmp42 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{parameter1, tmp39});
    tmp43 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch45__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch45__label);
    tmp44 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp42}, TNode<JSAny>{tmp43}, TNode<JSAny>{tmp36}, TNode<JSAny>{tmp8});
    }
    if (catch45__label.is_used()) {
      compiler::CodeAssemblerLabel catch45_skip(&ca_);
      ca_.Goto(&catch45_skip);
      ca_.Bind(&catch45__label, &tmp46);
      ca_.Goto(&block22);
      ca_.Bind(&catch45_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch48__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch48__label);
    tmp47 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch48__label.is_used()) {
      compiler::CodeAssemblerLabel catch48_skip(&ca_);
      ca_.Goto(&catch48_skip);
      ca_.Bind(&catch48__label, &tmp49);
      ca_.Goto(&block23);
      ca_.Bind(&catch48_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch51__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch51__label);
    tmp50 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch51__label.is_used()) {
      compiler::CodeAssemblerLabel catch51_skip(&ca_);
      ca_.Goto(&catch51_skip);
      ca_.Bind(&catch51__label, &tmp52);
      ca_.Goto(&block24);
      ca_.Bind(&catch51_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch54__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch54__label);
    tmp53 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp8}, TNode<Number>{tmp50});
    }
    if (catch54__label.is_used()) {
      compiler::CodeAssemblerLabel catch54_skip(&ca_);
      ca_.Goto(&catch54_skip);
      ca_.Bind(&catch54__label, &tmp55);
      ca_.Goto(&block25);
      ca_.Bind(&catch54_skip);
    }
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{parameter1, tmp47}, tmp53);
    compiler::CodeAssemblerExceptionHandlerLabel catch57__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch57__label);
    tmp56 = ToBoolean_0(state_, TNode<JSAny>{tmp44});
    }
    if (catch57__label.is_used()) {
      compiler::CodeAssemblerLabel catch57_skip(&ca_);
      ca_.Goto(&catch57_skip);
      ca_.Bind(&catch57__label, &tmp58);
      ca_.Goto(&block28);
      ca_.Bind(&catch57_skip);
    }
    ca_.Branch(tmp56, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp59;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp59 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp30, tmp59);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp60;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp60 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp35, tmp60);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp61;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp61 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp38, tmp61);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp62;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp62 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp41, tmp62);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp63;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp63 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp46, tmp63);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp64;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp64 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp49, tmp64);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp65;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp65 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp52, tmp65);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp66;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp66 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp55, tmp66);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp67;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp67 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp58, tmp67);
  }

      TNode<JSAny> tmp69;
  TNode<False> tmp70;
  TNode<JSObject> tmp71;
      TNode<JSAny> tmp73;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    compiler::CodeAssemblerExceptionHandlerLabel catch68__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch68__label);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch68__label.is_used()) {
      compiler::CodeAssemblerLabel catch68_skip(&ca_);
      ca_.Goto(&catch68_skip);
      ca_.Bind(&catch68__label, &tmp69);
      ca_.Goto(&block29);
      ca_.Bind(&catch68_skip);
    }
    tmp70 = False_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch72__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch72__label);
    tmp71 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp36}, TNode<Boolean>{tmp70});
    }
    if (catch72__label.is_used()) {
      compiler::CodeAssemblerLabel catch72_skip(&ca_);
      ca_.Goto(&catch72_skip);
      ca_.Bind(&catch72__label, &tmp73);
      ca_.Goto(&block30);
      ca_.Bind(&catch72_skip);
    }
    CodeStubAssembler(state_).Return(tmp71);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp74;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp74 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp69, tmp74);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp75;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp75 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block20, tmp73, tmp75);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block5);
  }

  TNode<JSAny> phi_bb20_6;
  TNode<Union<JSMessageObject, TheHole>> phi_bb20_7;
  TNode<IntPtrT> tmp76;
      TNode<JSAny> tmp78;
  TNode<JSReceiver> tmp79;
      TNode<JSAny> tmp81;
      TNode<JSAny> tmp83;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_6, &phi_bb20_7);
    compiler::CodeAssemblerExceptionHandlerLabel catch77__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch77__label);
    tmp76 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch77__label.is_used()) {
      compiler::CodeAssemblerLabel catch77_skip(&ca_);
      ca_.Goto(&catch77_skip);
      ca_.Bind(&catch77__label, &tmp78);
      ca_.Goto(&block31);
      ca_.Bind(&catch77_skip);
    }
    tmp79 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp76});
    compiler::CodeAssemblerExceptionHandlerLabel catch80__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch80__label);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp79});
    }
    if (catch80__label.is_used()) {
      compiler::CodeAssemblerLabel catch80_skip(&ca_);
      ca_.Goto(&catch80_skip);
      ca_.Bind(&catch80__label, &tmp81);
      ca_.Goto(&block32);
      ca_.Bind(&catch80_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch82__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch82__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb20_6, phi_bb20_7);
    CodeStubAssembler(state_).Unreachable();
    }
    if (catch82__label.is_used()) {
      compiler::CodeAssemblerLabel catch82_skip(&ca_);
      ca_.Bind(&catch82__label, &tmp83);
      ca_.Goto(&block33);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp84;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp84 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp78, tmp84);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp85;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp85 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp81, tmp85);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp86;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp86 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp83, tmp86);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:425:3");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb2_3;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb2_3, phi_bb2_4);
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=430&c=1
TNode<JSIteratorTakeHelper> NewJSIteratorTakeHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Number> p_limit) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<FixedArray> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Uint32T> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<JSIteratorTakeHelper> tmp20;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ITERATOR_TAKE_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = kEmptyFixedArray_0(state_);
    tmp5 = kEmptyFixedArray_0(state_);
    tmp6 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp7 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp6});
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp11 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp10}, TNode<Map>{tmp3}, TNode<BoolT>{tmp8}, TNode<BoolT>{tmp9});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp11, tmp12}, tmp3);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp11, tmp13}, tmp4);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp11, tmp14}, tmp5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp15}, tmp7);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp11, tmp16}, p_underlying.object);
    tmp17 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp17});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp11, tmp18}, p_underlying.next);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp11, tmp19}, p_limit);
    tmp20 = TORQUE_CAST(TNode<HeapObject>{tmp11});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSIteratorTakeHelper>{tmp20};
}

TF_BUILTIN(IteratorPrototypeTake, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kLimit);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.take");
  }

  TNode<Number> tmp2;
      TNode<JSAny> tmp4;
  TNode<BoolT> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerExceptionHandlerLabel catch3__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch3__label);
    tmp2 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter2});
    }
    if (catch3__label.is_used()) {
      compiler::CodeAssemblerLabel catch3_skip(&ca_);
      ca_.Goto(&catch3_skip);
      ca_.Bind(&catch3__label, &tmp4);
      ca_.Goto(&block9);
      ca_.Bind(&catch3_skip);
    }
    tmp5 = NumberIsNaN_0(state_, TNode<Number>{tmp2});
    ca_.Branch(tmp5, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp6;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp6 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp4, tmp6);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block2);
  }

  TNode<Number> tmp7;
  TNode<Number> tmp8;
  TNode<BoolT> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp7 = ToInteger_Inline_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp2});
    tmp8 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp9 = NumberIsLessThan_0(state_, TNode<Number>{tmp7}, TNode<Number>{tmp8});
    ca_.Branch(tmp9, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block2);
  }

  TNode<JSReceiver> tmp10;
  TNode<JSAny> tmp11;
  TNode<JSIteratorTakeHelper> tmp12;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    std::tie(tmp10, tmp11) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp12 = NewJSIteratorTakeHelper_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp10}, TNode<JSAny>{tmp11}}, TNode<Number>{tmp7});
    CodeStubAssembler(state_).Return(tmp12);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kMustBePositive), TNode<Object>{parameter2});
  }
}

TF_BUILTIN(IteratorTakeHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorTakeHelper> parameter1 = UncheckedParameter<JSIteratorTakeHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Map> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<Number> tmp2;
  TNode<Number> tmp3;
      TNode<JSAny> tmp5;
  TNode<BoolT> tmp6;
      TNode<JSAny> tmp8;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp2 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{parameter1, tmp1});
    compiler::CodeAssemblerExceptionHandlerLabel catch4__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch4__label);
    tmp3 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    }
    if (catch4__label.is_used()) {
      compiler::CodeAssemblerLabel catch4_skip(&ca_);
      ca_.Goto(&catch4_skip);
      ca_.Bind(&catch4__label, &tmp5);
      ca_.Goto(&block5);
      ca_.Bind(&catch4_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch7__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch7__label);
    tmp6 = IsNumberEqual_0(state_, TNode<Number>{tmp2}, TNode<Number>{tmp3});
    }
    if (catch7__label.is_used()) {
      compiler::CodeAssemblerLabel catch7_skip(&ca_);
      ca_.Goto(&catch7_skip);
      ca_.Bind(&catch7__label, &tmp8);
      ca_.Goto(&block6);
      ca_.Bind(&catch7_skip);
    }
    ca_.Branch(tmp6, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp5, tmp9);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp8, tmp10);
  }

      TNode<JSAny> tmp12;
  TNode<IntPtrT> tmp13;
      TNode<JSAny> tmp15;
  TNode<JSReceiver> tmp16;
  TNode<IntPtrT> tmp17;
      TNode<JSAny> tmp19;
  TNode<IntPtrT> tmp20;
      TNode<JSAny> tmp22;
  TNode<JSAny> tmp23;
      TNode<JSAny> tmp25;
  TNode<Undefined> tmp26;
  TNode<True> tmp27;
  TNode<JSObject> tmp28;
      TNode<JSAny> tmp30;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerExceptionHandlerLabel catch11__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch11__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch11__label.is_used()) {
      compiler::CodeAssemblerLabel catch11_skip(&ca_);
      ca_.Goto(&catch11_skip);
      ca_.Bind(&catch11__label, &tmp12);
      ca_.Goto(&block7);
      ca_.Bind(&catch11_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch14__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch14__label);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch14__label.is_used()) {
      compiler::CodeAssemblerLabel catch14_skip(&ca_);
      ca_.Goto(&catch14_skip);
      ca_.Bind(&catch14__label, &tmp15);
      ca_.Goto(&block8);
      ca_.Bind(&catch14_skip);
    }
    tmp16 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp13});
    compiler::CodeAssemblerExceptionHandlerLabel catch18__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch18__label);
    tmp17 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch18__label.is_used()) {
      compiler::CodeAssemblerLabel catch18_skip(&ca_);
      ca_.Goto(&catch18_skip);
      ca_.Bind(&catch18__label, &tmp19);
      ca_.Goto(&block9);
      ca_.Bind(&catch18_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch21__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch21__label);
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp17});
    }
    if (catch21__label.is_used()) {
      compiler::CodeAssemblerLabel catch21_skip(&ca_);
      ca_.Goto(&catch21_skip);
      ca_.Bind(&catch21__label, &tmp22);
      ca_.Goto(&block10);
      ca_.Bind(&catch21_skip);
    }
    tmp23 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp20});
    compiler::CodeAssemblerExceptionHandlerLabel catch24__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch24__label);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp16}, TNode<JSAny>{tmp23}});
    }
    if (catch24__label.is_used()) {
      compiler::CodeAssemblerLabel catch24_skip(&ca_);
      ca_.Goto(&catch24_skip);
      ca_.Bind(&catch24__label, &tmp25);
      ca_.Goto(&block11);
      ca_.Bind(&catch24_skip);
    }
    tmp26 = Undefined_0(state_);
    tmp27 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch29__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch29__label);
    tmp28 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp26}, TNode<Boolean>{tmp27});
    }
    if (catch29__label.is_used()) {
      compiler::CodeAssemblerLabel catch29_skip(&ca_);
      ca_.Goto(&catch29_skip);
      ca_.Bind(&catch29__label, &tmp30);
      ca_.Goto(&block12);
      ca_.Bind(&catch29_skip);
    }
    CodeStubAssembler(state_).Return(tmp28);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp31;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp31 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp12, tmp31);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp32;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp32 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp15, tmp32);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp33;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp33 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp19, tmp33);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp34;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp34 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp22, tmp34);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp35;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp35 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp25, tmp35);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp36;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp36 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp30, tmp36);
  }

  TNode<BoolT> tmp37;
      TNode<JSAny> tmp39;
  TNode<BoolT> tmp40;
      TNode<JSAny> tmp42;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    compiler::CodeAssemblerExceptionHandlerLabel catch38__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch38__label);
    tmp37 = NumberIsSomeInfinity_0(state_, TNode<Number>{tmp2});
    }
    if (catch38__label.is_used()) {
      compiler::CodeAssemblerLabel catch38_skip(&ca_);
      ca_.Goto(&catch38_skip);
      ca_.Bind(&catch38__label, &tmp39);
      ca_.Goto(&block15);
      ca_.Bind(&catch38_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch41__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch41__label);
    tmp40 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp37});
    }
    if (catch41__label.is_used()) {
      compiler::CodeAssemblerLabel catch41_skip(&ca_);
      ca_.Goto(&catch41_skip);
      ca_.Bind(&catch41__label, &tmp42);
      ca_.Goto(&block16);
      ca_.Bind(&catch41_skip);
    }
    ca_.Branch(tmp40, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp43;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp43 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp39, tmp43);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp44;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp44 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp42, tmp44);
  }

  TNode<IntPtrT> tmp45;
      TNode<JSAny> tmp47;
  TNode<Number> tmp48;
      TNode<JSAny> tmp50;
  TNode<Number> tmp51;
      TNode<JSAny> tmp53;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    compiler::CodeAssemblerExceptionHandlerLabel catch46__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch46__label);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch46__label.is_used()) {
      compiler::CodeAssemblerLabel catch46_skip(&ca_);
      ca_.Goto(&catch46_skip);
      ca_.Bind(&catch46__label, &tmp47);
      ca_.Goto(&block17);
      ca_.Bind(&catch46_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch49__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch49__label);
    tmp48 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch49__label.is_used()) {
      compiler::CodeAssemblerLabel catch49_skip(&ca_);
      ca_.Goto(&catch49_skip);
      ca_.Bind(&catch49__label, &tmp50);
      ca_.Goto(&block18);
      ca_.Bind(&catch49_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch52__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch52__label);
    tmp51 = CodeStubAssembler(state_).NumberSub(TNode<Number>{tmp2}, TNode<Number>{tmp48});
    }
    if (catch52__label.is_used()) {
      compiler::CodeAssemblerLabel catch52_skip(&ca_);
      ca_.Goto(&catch52_skip);
      ca_.Bind(&catch52__label, &tmp53);
      ca_.Goto(&block19);
      ca_.Bind(&catch52_skip);
    }
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{parameter1, tmp45}, tmp51);
    ca_.Goto(&block14);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp54;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp54 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp47, tmp54);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp55;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp55 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp50, tmp55);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp56;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp56 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp53, tmp56);
  }

  TNode<IntPtrT> tmp57;
      TNode<JSAny> tmp59;
  TNode<JSReceiver> tmp60;
  TNode<IntPtrT> tmp61;
      TNode<JSAny> tmp63;
  TNode<IntPtrT> tmp64;
      TNode<JSAny> tmp66;
  TNode<JSAny> tmp67;
  TNode<JSReceiver> tmp68;
      TNode<JSAny> tmp71;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    compiler::CodeAssemblerExceptionHandlerLabel catch58__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch58__label);
    tmp57 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch58__label.is_used()) {
      compiler::CodeAssemblerLabel catch58_skip(&ca_);
      ca_.Goto(&catch58_skip);
      ca_.Bind(&catch58__label, &tmp59);
      ca_.Goto(&block22);
      ca_.Bind(&catch58_skip);
    }
    tmp60 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp57});
    compiler::CodeAssemblerExceptionHandlerLabel catch62__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch62__label);
    tmp61 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch62__label.is_used()) {
      compiler::CodeAssemblerLabel catch62_skip(&ca_);
      ca_.Goto(&catch62_skip);
      ca_.Bind(&catch62__label, &tmp63);
      ca_.Goto(&block23);
      ca_.Bind(&catch62_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch65__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch65__label);
    tmp64 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp57}, TNode<IntPtrT>{tmp61});
    }
    if (catch65__label.is_used()) {
      compiler::CodeAssemblerLabel catch65_skip(&ca_);
      ca_.Goto(&catch65_skip);
      ca_.Bind(&catch65__label, &tmp66);
      ca_.Goto(&block24);
      ca_.Bind(&catch65_skip);
    }
    tmp67 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp64});
    compiler::CodeAssemblerLabel label69(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch70__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch70__label);
    tmp68 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp60}, TNode<JSAny>{tmp67}}, TNode<Map>{tmp0}, &label69);
    }
    if (catch70__label.is_used()) {
      compiler::CodeAssemblerLabel catch70_skip(&ca_);
      ca_.Goto(&catch70_skip);
      ca_.Bind(&catch70__label, &tmp71);
      ca_.Goto(&block27);
      ca_.Bind(&catch70_skip);
    }
    ca_.Goto(&block25);
    if (label69.is_used()) {
      ca_.Bind(&label69);
      ca_.Goto(&block26);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp72;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp72 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp59, tmp72);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp73;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp73 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp63, tmp73);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp74;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp74 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp66, tmp74);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp75;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp75 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp71, tmp75);
  }

      TNode<JSAny> tmp77;
  TNode<Undefined> tmp78;
  TNode<True> tmp79;
  TNode<JSObject> tmp80;
      TNode<JSAny> tmp82;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    compiler::CodeAssemblerExceptionHandlerLabel catch76__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch76__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch76__label.is_used()) {
      compiler::CodeAssemblerLabel catch76_skip(&ca_);
      ca_.Goto(&catch76_skip);
      ca_.Bind(&catch76__label, &tmp77);
      ca_.Goto(&block28);
      ca_.Bind(&catch76_skip);
    }
    tmp78 = Undefined_0(state_);
    tmp79 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch81__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch81__label);
    tmp80 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp78}, TNode<Boolean>{tmp79});
    }
    if (catch81__label.is_used()) {
      compiler::CodeAssemblerLabel catch81_skip(&ca_);
      ca_.Goto(&catch81_skip);
      ca_.Bind(&catch81__label, &tmp82);
      ca_.Goto(&block29);
      ca_.Bind(&catch81_skip);
    }
    CodeStubAssembler(state_).Return(tmp80);
  }

  TNode<JSAny> tmp83;
      TNode<JSAny> tmp85;
      TNode<JSAny> tmp87;
  TNode<False> tmp88;
  TNode<JSObject> tmp89;
      TNode<JSAny> tmp91;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    compiler::CodeAssemblerExceptionHandlerLabel catch84__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch84__label);
    tmp83 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp68}, TNode<Map>{tmp0});
    }
    if (catch84__label.is_used()) {
      compiler::CodeAssemblerLabel catch84_skip(&ca_);
      ca_.Goto(&catch84_skip);
      ca_.Bind(&catch84__label, &tmp85);
      ca_.Goto(&block30);
      ca_.Bind(&catch84_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch86__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch86__label);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch86__label.is_used()) {
      compiler::CodeAssemblerLabel catch86_skip(&ca_);
      ca_.Goto(&catch86_skip);
      ca_.Bind(&catch86__label, &tmp87);
      ca_.Goto(&block31);
      ca_.Bind(&catch86_skip);
    }
    tmp88 = False_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch90__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch90__label);
    tmp89 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp83}, TNode<Boolean>{tmp88});
    }
    if (catch90__label.is_used()) {
      compiler::CodeAssemblerLabel catch90_skip(&ca_);
      ca_.Goto(&catch90_skip);
      ca_.Bind(&catch90__label, &tmp91);
      ca_.Goto(&block32);
      ca_.Bind(&catch90_skip);
    }
    CodeStubAssembler(state_).Return(tmp89);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp92;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp92 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp77, tmp92);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp93;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp93 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp82, tmp93);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp94;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp94 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp85, tmp94);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp95;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp95 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp87, tmp95);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp96;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp96 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp91, tmp96);
  }

  TNode<JSAny> phi_bb2_4;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_5;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4, &phi_bb2_5);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb2_4, phi_bb2_5);
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=551&c=1
TNode<JSIteratorDropHelper> NewJSIteratorDropHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Number> p_limit) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<FixedArray> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Uint32T> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<JSIteratorDropHelper> tmp20;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ITERATOR_DROP_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = kEmptyFixedArray_0(state_);
    tmp5 = kEmptyFixedArray_0(state_);
    tmp6 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp7 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp6});
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp11 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp10}, TNode<Map>{tmp3}, TNode<BoolT>{tmp8}, TNode<BoolT>{tmp9});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp11, tmp12}, tmp3);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp11, tmp13}, tmp4);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp11, tmp14}, tmp5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp15}, tmp7);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp11, tmp16}, p_underlying.object);
    tmp17 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp17});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp11, tmp18}, p_underlying.next);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp11, tmp19}, p_limit);
    tmp20 = TORQUE_CAST(TNode<HeapObject>{tmp11});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSIteratorDropHelper>{tmp20};
}

TF_BUILTIN(IteratorPrototypeDrop, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kLimit);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.drop");
  }

  TNode<Number> tmp2;
      TNode<JSAny> tmp4;
  TNode<BoolT> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerExceptionHandlerLabel catch3__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch3__label);
    tmp2 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter2});
    }
    if (catch3__label.is_used()) {
      compiler::CodeAssemblerLabel catch3_skip(&ca_);
      ca_.Goto(&catch3_skip);
      ca_.Bind(&catch3__label, &tmp4);
      ca_.Goto(&block9);
      ca_.Bind(&catch3_skip);
    }
    tmp5 = NumberIsNaN_0(state_, TNode<Number>{tmp2});
    ca_.Branch(tmp5, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp6;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp6 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp4, tmp6);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block2);
  }

  TNode<Number> tmp7;
  TNode<Number> tmp8;
  TNode<BoolT> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp7 = ToInteger_Inline_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp2});
    tmp8 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp9 = NumberIsLessThan_0(state_, TNode<Number>{tmp7}, TNode<Number>{tmp8});
    ca_.Branch(tmp9, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block2);
  }

  TNode<JSReceiver> tmp10;
  TNode<JSAny> tmp11;
  TNode<JSIteratorDropHelper> tmp12;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    std::tie(tmp10, tmp11) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp12 = NewJSIteratorDropHelper_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp10}, TNode<JSAny>{tmp11}}, TNode<Number>{tmp7});
    CodeStubAssembler(state_).Return(tmp12);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kMustBePositive), TNode<Object>{parameter2});
  }
}

TF_BUILTIN(IteratorDropHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorDropHelper> parameter1 = UncheckedParameter<JSIteratorDropHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Number> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Number> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block25(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block33(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Map> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<Number> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp2 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{parameter1, tmp1});
    ca_.Goto(&block7, tmp2);
  }

  TNode<Number> phi_bb7_3;
  TNode<Number> tmp3;
      TNode<JSAny> tmp5;
  TNode<BoolT> tmp6;
      TNode<JSAny> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch4__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch4__label);
    tmp3 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    }
    if (catch4__label.is_used()) {
      compiler::CodeAssemblerLabel catch4_skip(&ca_);
      ca_.Goto(&catch4_skip);
      ca_.Bind(&catch4__label, &tmp5);
      ca_.Goto(&block8, phi_bb7_3, phi_bb7_3, phi_bb7_3);
      ca_.Bind(&catch4_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch7__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch7__label);
    tmp6 = NumberIsGreaterThan_0(state_, TNode<Number>{phi_bb7_3}, TNode<Number>{tmp3});
    }
    if (catch7__label.is_used()) {
      compiler::CodeAssemblerLabel catch7_skip(&ca_);
      ca_.Goto(&catch7_skip);
      ca_.Bind(&catch7__label, &tmp8);
      ca_.Goto(&block9, phi_bb7_3, phi_bb7_3);
      ca_.Bind(&catch7_skip);
    }
    ca_.Branch(tmp6, &block5, std::vector<compiler::Node*>{phi_bb7_3}, &block6, std::vector<compiler::Node*>{phi_bb7_3});
  }

  TNode<Number> phi_bb8_3;
  TNode<Number> phi_bb8_5;
  TNode<Number> phi_bb8_6;
  TNode<Union<JSMessageObject, TheHole>> tmp9;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_3, &phi_bb8_5, &phi_bb8_6);
    tmp9 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb8_3, tmp5, tmp9);
  }

  TNode<Number> phi_bb9_3;
  TNode<Number> phi_bb9_5;
  TNode<Union<JSMessageObject, TheHole>> tmp10;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3, &phi_bb9_5);
    tmp10 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb9_3, tmp8, tmp10);
  }

  TNode<Number> phi_bb5_3;
  TNode<BoolT> tmp11;
      TNode<JSAny> tmp13;
  TNode<BoolT> tmp14;
      TNode<JSAny> tmp16;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch12__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch12__label);
    tmp11 = NumberIsSomeInfinity_0(state_, TNode<Number>{phi_bb5_3});
    }
    if (catch12__label.is_used()) {
      compiler::CodeAssemblerLabel catch12_skip(&ca_);
      ca_.Goto(&catch12_skip);
      ca_.Bind(&catch12__label, &tmp13);
      ca_.Goto(&block12, phi_bb5_3, phi_bb5_3);
      ca_.Bind(&catch12_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp11});
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block13, phi_bb5_3);
      ca_.Bind(&catch15_skip);
    }
    ca_.Branch(tmp14, &block10, std::vector<compiler::Node*>{phi_bb5_3}, &block11, std::vector<compiler::Node*>{phi_bb5_3});
  }

  TNode<Number> phi_bb12_3;
  TNode<Number> phi_bb12_5;
  TNode<Union<JSMessageObject, TheHole>> tmp17;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_3, &phi_bb12_5);
    tmp17 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb12_3, tmp13, tmp17);
  }

  TNode<Number> phi_bb13_3;
  TNode<Union<JSMessageObject, TheHole>> tmp18;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_3);
    tmp18 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb13_3, tmp16, tmp18);
  }

  TNode<Number> phi_bb10_3;
  TNode<Number> tmp19;
      TNode<JSAny> tmp21;
  TNode<Number> tmp22;
      TNode<JSAny> tmp24;
  TNode<IntPtrT> tmp25;
      TNode<JSAny> tmp27;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch20__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch20__label);
    tmp19 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch20__label.is_used()) {
      compiler::CodeAssemblerLabel catch20_skip(&ca_);
      ca_.Goto(&catch20_skip);
      ca_.Bind(&catch20__label, &tmp21);
      ca_.Goto(&block14, phi_bb10_3, phi_bb10_3, phi_bb10_3);
      ca_.Bind(&catch20_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch23__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch23__label);
    tmp22 = CodeStubAssembler(state_).NumberSub(TNode<Number>{phi_bb10_3}, TNode<Number>{tmp19});
    }
    if (catch23__label.is_used()) {
      compiler::CodeAssemblerLabel catch23_skip(&ca_);
      ca_.Goto(&catch23_skip);
      ca_.Bind(&catch23__label, &tmp24);
      ca_.Goto(&block15, phi_bb10_3, phi_bb10_3);
      ca_.Bind(&catch23_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch26__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch26__label);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch26__label.is_used()) {
      compiler::CodeAssemblerLabel catch26_skip(&ca_);
      ca_.Goto(&catch26_skip);
      ca_.Bind(&catch26__label, &tmp27);
      ca_.Goto(&block16);
      ca_.Bind(&catch26_skip);
    }
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{parameter1, tmp25}, tmp22);
    ca_.Goto(&block11, tmp22);
  }

  TNode<Number> phi_bb14_3;
  TNode<Number> phi_bb14_5;
  TNode<Number> phi_bb14_6;
  TNode<Union<JSMessageObject, TheHole>> tmp28;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_3, &phi_bb14_5, &phi_bb14_6);
    tmp28 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb14_3, tmp21, tmp28);
  }

  TNode<Number> phi_bb15_3;
  TNode<Number> phi_bb15_5;
  TNode<Union<JSMessageObject, TheHole>> tmp29;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_3, &phi_bb15_5);
    tmp29 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb15_3, tmp24, tmp29);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp30;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp30 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp22, tmp27, tmp30);
  }

  TNode<Number> phi_bb11_3;
  TNode<IntPtrT> tmp31;
      TNode<JSAny> tmp33;
  TNode<JSReceiver> tmp34;
  TNode<IntPtrT> tmp35;
      TNode<JSAny> tmp37;
  TNode<IntPtrT> tmp38;
      TNode<JSAny> tmp40;
  TNode<JSAny> tmp41;
  TNode<JSReceiver> tmp42;
      TNode<JSAny> tmp45;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch32__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch32__label);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch32__label.is_used()) {
      compiler::CodeAssemblerLabel catch32_skip(&ca_);
      ca_.Goto(&catch32_skip);
      ca_.Bind(&catch32__label, &tmp33);
      ca_.Goto(&block17);
      ca_.Bind(&catch32_skip);
    }
    tmp34 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp31});
    compiler::CodeAssemblerExceptionHandlerLabel catch36__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch36__label);
    tmp35 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch36__label.is_used()) {
      compiler::CodeAssemblerLabel catch36_skip(&ca_);
      ca_.Goto(&catch36_skip);
      ca_.Bind(&catch36__label, &tmp37);
      ca_.Goto(&block18);
      ca_.Bind(&catch36_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch39__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch39__label);
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp31}, TNode<IntPtrT>{tmp35});
    }
    if (catch39__label.is_used()) {
      compiler::CodeAssemblerLabel catch39_skip(&ca_);
      ca_.Goto(&catch39_skip);
      ca_.Bind(&catch39__label, &tmp40);
      ca_.Goto(&block19);
      ca_.Bind(&catch39_skip);
    }
    tmp41 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp38});
    compiler::CodeAssemblerLabel label43(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch44__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch44__label);
    tmp42 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp34}, TNode<JSAny>{tmp41}}, TNode<Map>{tmp0}, &label43);
    }
    if (catch44__label.is_used()) {
      compiler::CodeAssemblerLabel catch44_skip(&ca_);
      ca_.Goto(&catch44_skip);
      ca_.Bind(&catch44__label, &tmp45);
      ca_.Goto(&block22);
      ca_.Bind(&catch44_skip);
    }
    ca_.Goto(&block20);
    if (label43.is_used()) {
      ca_.Bind(&label43);
      ca_.Goto(&block21);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp46;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp46 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb11_3, tmp33, tmp46);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp47;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp47 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb11_3, tmp37, tmp47);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp48;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp48 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb11_3, tmp40, tmp48);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp49;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp49 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb11_3, tmp45, tmp49);
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    ca_.Goto(&block4, phi_bb11_3);
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block7, phi_bb11_3);
  }

  TNode<Number> phi_bb6_3;
  TNode<IntPtrT> tmp50;
      TNode<JSAny> tmp52;
  TNode<JSReceiver> tmp53;
  TNode<IntPtrT> tmp54;
      TNode<JSAny> tmp56;
  TNode<IntPtrT> tmp57;
      TNode<JSAny> tmp59;
  TNode<JSAny> tmp60;
  TNode<JSReceiver> tmp61;
      TNode<JSAny> tmp64;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch51__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch51__label);
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch51__label.is_used()) {
      compiler::CodeAssemblerLabel catch51_skip(&ca_);
      ca_.Goto(&catch51_skip);
      ca_.Bind(&catch51__label, &tmp52);
      ca_.Goto(&block23, phi_bb6_3);
      ca_.Bind(&catch51_skip);
    }
    tmp53 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp50});
    compiler::CodeAssemblerExceptionHandlerLabel catch55__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch55__label);
    tmp54 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch55__label.is_used()) {
      compiler::CodeAssemblerLabel catch55_skip(&ca_);
      ca_.Goto(&catch55_skip);
      ca_.Bind(&catch55__label, &tmp56);
      ca_.Goto(&block24, phi_bb6_3);
      ca_.Bind(&catch55_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch58__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch58__label);
    tmp57 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp50}, TNode<IntPtrT>{tmp54});
    }
    if (catch58__label.is_used()) {
      compiler::CodeAssemblerLabel catch58_skip(&ca_);
      ca_.Goto(&catch58_skip);
      ca_.Bind(&catch58__label, &tmp59);
      ca_.Goto(&block25, phi_bb6_3);
      ca_.Bind(&catch58_skip);
    }
    tmp60 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp57});
    compiler::CodeAssemblerLabel label62(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch63__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch63__label);
    tmp61 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp53}, TNode<JSAny>{tmp60}}, TNode<Map>{tmp0}, &label62);
    }
    if (catch63__label.is_used()) {
      compiler::CodeAssemblerLabel catch63_skip(&ca_);
      ca_.Goto(&catch63_skip);
      ca_.Bind(&catch63__label, &tmp64);
      ca_.Goto(&block28, phi_bb6_3);
      ca_.Bind(&catch63_skip);
    }
    ca_.Goto(&block26, phi_bb6_3);
    if (label62.is_used()) {
      ca_.Bind(&label62);
      ca_.Goto(&block27, phi_bb6_3);
    }
  }

  TNode<Number> phi_bb23_3;
  TNode<Union<JSMessageObject, TheHole>> tmp65;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_3);
    tmp65 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb23_3, tmp52, tmp65);
  }

  TNode<Number> phi_bb24_3;
  TNode<Union<JSMessageObject, TheHole>> tmp66;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_3);
    tmp66 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb24_3, tmp56, tmp66);
  }

  TNode<Number> phi_bb25_3;
  TNode<Union<JSMessageObject, TheHole>> tmp67;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_3);
    tmp67 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb25_3, tmp59, tmp67);
  }

  TNode<Number> phi_bb28_3;
  TNode<Union<JSMessageObject, TheHole>> tmp68;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_3);
    tmp68 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb28_3, tmp64, tmp68);
  }

  TNode<Number> phi_bb27_3;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_3);
    ca_.Goto(&block4, phi_bb27_3);
  }

  TNode<Number> phi_bb26_3;
  TNode<JSAny> tmp69;
      TNode<JSAny> tmp71;
      TNode<JSAny> tmp73;
  TNode<False> tmp74;
  TNode<JSObject> tmp75;
      TNode<JSAny> tmp77;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch70__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch70__label);
    tmp69 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp61}, TNode<Map>{tmp0});
    }
    if (catch70__label.is_used()) {
      compiler::CodeAssemblerLabel catch70_skip(&ca_);
      ca_.Goto(&catch70_skip);
      ca_.Bind(&catch70__label, &tmp71);
      ca_.Goto(&block31, phi_bb26_3);
      ca_.Bind(&catch70_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch72__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch72__label);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch72__label.is_used()) {
      compiler::CodeAssemblerLabel catch72_skip(&ca_);
      ca_.Goto(&catch72_skip);
      ca_.Bind(&catch72__label, &tmp73);
      ca_.Goto(&block32, phi_bb26_3);
      ca_.Bind(&catch72_skip);
    }
    tmp74 = False_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch76__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch76__label);
    tmp75 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp69}, TNode<Boolean>{tmp74});
    }
    if (catch76__label.is_used()) {
      compiler::CodeAssemblerLabel catch76_skip(&ca_);
      ca_.Goto(&catch76_skip);
      ca_.Bind(&catch76__label, &tmp77);
      ca_.Goto(&block33, phi_bb26_3);
      ca_.Bind(&catch76_skip);
    }
    CodeStubAssembler(state_).Return(tmp75);
  }

  TNode<Number> phi_bb4_3;
      TNode<JSAny> tmp79;
  TNode<Undefined> tmp80;
  TNode<True> tmp81;
  TNode<JSObject> tmp82;
      TNode<JSAny> tmp84;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch78__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch78__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch78__label.is_used()) {
      compiler::CodeAssemblerLabel catch78_skip(&ca_);
      ca_.Goto(&catch78_skip);
      ca_.Bind(&catch78__label, &tmp79);
      ca_.Goto(&block29);
      ca_.Bind(&catch78_skip);
    }
    tmp80 = Undefined_0(state_);
    tmp81 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch83__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch83__label);
    tmp82 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp80}, TNode<Boolean>{tmp81});
    }
    if (catch83__label.is_used()) {
      compiler::CodeAssemblerLabel catch83_skip(&ca_);
      ca_.Goto(&catch83_skip);
      ca_.Bind(&catch83__label, &tmp84);
      ca_.Goto(&block30);
      ca_.Bind(&catch83_skip);
    }
    CodeStubAssembler(state_).Return(tmp82);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp85;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp85 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb4_3, tmp79, tmp85);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp86;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp86 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb4_3, tmp84, tmp86);
  }

  TNode<Number> phi_bb31_3;
  TNode<Union<JSMessageObject, TheHole>> tmp87;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_3);
    tmp87 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb31_3, tmp71, tmp87);
  }

  TNode<Number> phi_bb32_3;
  TNode<Union<JSMessageObject, TheHole>> tmp88;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_3);
    tmp88 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb32_3, tmp73, tmp88);
  }

  TNode<Number> phi_bb33_3;
  TNode<Union<JSMessageObject, TheHole>> tmp89;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_3);
    tmp89 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb33_3, tmp77, tmp89);
  }

  TNode<Number> phi_bb2_3;
  TNode<JSAny> phi_bb2_4;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_5;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4, &phi_bb2_5);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb2_4, phi_bb2_5);
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=672&c=1
const char* kFlatMapMethodName_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return "Iterator.prototype.flatMap";}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=674&c=1
TNode<JSIteratorFlatMapHelper> NewJSIteratorFlatMapHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_mapper) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<FixedArray> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Uint32T> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<HeapObject> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Number> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<JSIteratorFlatMapHelper> tmp25;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ITERATOR_FLAT_MAP_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = kEmptyFixedArray_0(state_);
    tmp5 = kEmptyFixedArray_0(state_);
    tmp6 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp7 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp6});
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp11 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp10}, TNode<Map>{tmp3}, TNode<BoolT>{tmp8}, TNode<BoolT>{tmp9});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp11, tmp12}, tmp3);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp11, tmp13}, tmp4);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp11, tmp14}, tmp5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp15}, tmp7);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp11, tmp16}, p_underlying.object);
    tmp17 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp17});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp11, tmp18}, p_underlying.next);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{tmp11, tmp19}, p_mapper);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp21 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp11, tmp20}, tmp21);
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp11, tmp22}, p_underlying.object);
    tmp23 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp24 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp23});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp11, tmp24}, p_underlying.next);
    tmp25 = TORQUE_CAST(TNode<HeapObject>{tmp11});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSIteratorFlatMapHelper>{tmp25};
}

TF_BUILTIN(IteratorPrototypeFlatMap, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kMapper);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), kFlatMapMethodName_0(state_));
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledNonCallable), kFlatMapMethodName_0(state_));
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<JSIteratorFlatMapHelper> tmp6;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = NewJSIteratorFlatMapHelper_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>{tmp2});
    CodeStubAssembler(state_).Return(tmp6);
  }
}

TF_BUILTIN(IteratorFlatMapHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorFlatMapHelper> parameter1 = UncheckedParameter<JSIteratorFlatMapHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block25(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block33(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block35(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block36(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSAny, Union<JSMessageObject, TheHole>> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block37(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block38(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block39(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block47(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block48(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block49(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block52(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block53(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block54(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block55(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSAny, Union<JSMessageObject, TheHole>> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block56(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block57(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block58(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block59(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Map> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    tmp1 = IteratorHelperIsSuspendedStart_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    ca_.Goto(&block5, tmp2);
  }

  TNode<BoolT> phi_bb5_3;
  TNode<BoolT> tmp3;
      TNode<JSAny> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch4__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch4__label);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch4__label.is_used()) {
      compiler::CodeAssemblerLabel catch4_skip(&ca_);
      ca_.Goto(&catch4_skip);
      ca_.Bind(&catch4__label, &tmp5);
      ca_.Goto(&block6, phi_bb5_3);
      ca_.Bind(&catch4_skip);
    }
    ca_.Branch(tmp3, &block3, std::vector<compiler::Node*>{phi_bb5_3}, &block4, std::vector<compiler::Node*>{phi_bb5_3});
  }

  TNode<BoolT> phi_bb6_3;
  TNode<Union<JSMessageObject, TheHole>> tmp6;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_3);
    tmp6 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb6_3, tmp5, tmp6);
  }

  TNode<BoolT> phi_bb3_3;
  TNode<IntPtrT> tmp7;
      TNode<JSAny> tmp9;
  TNode<Number> tmp10;
  TNode<BoolT> tmp11;
      TNode<JSAny> tmp13;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch8__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch8__label);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch8__label.is_used()) {
      compiler::CodeAssemblerLabel catch8_skip(&ca_);
      ca_.Goto(&catch8_skip);
      ca_.Bind(&catch8__label, &tmp9);
      ca_.Goto(&block7, phi_bb3_3);
      ca_.Bind(&catch8_skip);
    }
    tmp10 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{parameter1, tmp7});
    compiler::CodeAssemblerExceptionHandlerLabel catch12__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch12__label);
    tmp11 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb3_3});
    }
    if (catch12__label.is_used()) {
      compiler::CodeAssemblerLabel catch12_skip(&ca_);
      ca_.Goto(&catch12_skip);
      ca_.Bind(&catch12__label, &tmp13);
      ca_.Goto(&block10, phi_bb3_3, phi_bb3_3);
      ca_.Bind(&catch12_skip);
    }
    ca_.Branch(tmp11, &block8, std::vector<compiler::Node*>{phi_bb3_3}, &block9, std::vector<compiler::Node*>{phi_bb3_3});
  }

  TNode<BoolT> phi_bb7_3;
  TNode<Union<JSMessageObject, TheHole>> tmp14;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_3);
    tmp14 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb7_3, tmp9, tmp14);
  }

  TNode<BoolT> phi_bb10_3;
  TNode<BoolT> phi_bb10_5;
  TNode<Union<JSMessageObject, TheHole>> tmp15;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3, &phi_bb10_5);
    tmp15 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb10_3, tmp13, tmp15);
  }

  TNode<BoolT> phi_bb8_3;
  TNode<IntPtrT> tmp16;
      TNode<JSAny> tmp18;
  TNode<JSReceiver> tmp19;
  TNode<IntPtrT> tmp20;
      TNode<JSAny> tmp22;
  TNode<IntPtrT> tmp23;
      TNode<JSAny> tmp25;
  TNode<JSAny> tmp26;
  TNode<JSReceiver> tmp27;
      TNode<JSAny> tmp30;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch17__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch17__label);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch17__label.is_used()) {
      compiler::CodeAssemblerLabel catch17_skip(&ca_);
      ca_.Goto(&catch17_skip);
      ca_.Bind(&catch17__label, &tmp18);
      ca_.Goto(&block13, phi_bb8_3);
      ca_.Bind(&catch17_skip);
    }
    tmp19 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp16});
    compiler::CodeAssemblerExceptionHandlerLabel catch21__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch21__label);
    tmp20 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch21__label.is_used()) {
      compiler::CodeAssemblerLabel catch21_skip(&ca_);
      ca_.Goto(&catch21_skip);
      ca_.Bind(&catch21__label, &tmp22);
      ca_.Goto(&block14, phi_bb8_3);
      ca_.Bind(&catch21_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch24__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch24__label);
    tmp23 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp20});
    }
    if (catch24__label.is_used()) {
      compiler::CodeAssemblerLabel catch24_skip(&ca_);
      ca_.Goto(&catch24_skip);
      ca_.Bind(&catch24__label, &tmp25);
      ca_.Goto(&block15, phi_bb8_3);
      ca_.Bind(&catch24_skip);
    }
    tmp26 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp23});
    compiler::CodeAssemblerLabel label28(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch29__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch29__label);
    tmp27 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp19}, TNode<JSAny>{tmp26}}, TNode<Map>{tmp0}, &label28);
    }
    if (catch29__label.is_used()) {
      compiler::CodeAssemblerLabel catch29_skip(&ca_);
      ca_.Goto(&catch29_skip);
      ca_.Bind(&catch29__label, &tmp30);
      ca_.Goto(&block18, phi_bb8_3);
      ca_.Bind(&catch29_skip);
    }
    ca_.Goto(&block16, phi_bb8_3);
    if (label28.is_used()) {
      ca_.Bind(&label28);
      ca_.Goto(&block17, phi_bb8_3);
    }
  }

  TNode<BoolT> phi_bb13_3;
  TNode<Union<JSMessageObject, TheHole>> tmp31;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_3);
    tmp31 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb13_3, tmp18, tmp31);
  }

  TNode<BoolT> phi_bb14_3;
  TNode<Union<JSMessageObject, TheHole>> tmp32;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_3);
    tmp32 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb14_3, tmp22, tmp32);
  }

  TNode<BoolT> phi_bb15_3;
  TNode<Union<JSMessageObject, TheHole>> tmp33;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_3);
    tmp33 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb15_3, tmp25, tmp33);
  }

  TNode<BoolT> phi_bb18_3;
  TNode<Union<JSMessageObject, TheHole>> tmp34;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_3);
    tmp34 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb18_3, tmp30, tmp34);
  }

  TNode<BoolT> phi_bb17_3;
      TNode<JSAny> tmp36;
  TNode<Undefined> tmp37;
  TNode<True> tmp38;
  TNode<JSObject> tmp39;
      TNode<JSAny> tmp41;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch35__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch35__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch35__label.is_used()) {
      compiler::CodeAssemblerLabel catch35_skip(&ca_);
      ca_.Goto(&catch35_skip);
      ca_.Bind(&catch35__label, &tmp36);
      ca_.Goto(&block19, phi_bb17_3);
      ca_.Bind(&catch35_skip);
    }
    tmp37 = Undefined_0(state_);
    tmp38 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch40__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch40__label);
    tmp39 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp37}, TNode<Boolean>{tmp38});
    }
    if (catch40__label.is_used()) {
      compiler::CodeAssemblerLabel catch40_skip(&ca_);
      ca_.Goto(&catch40_skip);
      ca_.Bind(&catch40__label, &tmp41);
      ca_.Goto(&block20, phi_bb17_3);
      ca_.Bind(&catch40_skip);
    }
    CodeStubAssembler(state_).Return(tmp39);
  }

  TNode<BoolT> phi_bb16_3;
  TNode<JSAny> tmp42;
      TNode<JSAny> tmp44;
  TNode<IntPtrT> tmp45;
      TNode<JSAny> tmp47;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp48;
  TNode<Undefined> tmp49;
  TNode<JSAny> tmp50;
      TNode<JSAny> tmp52;
  TNode<JSReceiver> tmp53;
      TNode<JSAny> tmp56;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch43__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch43__label);
    tmp42 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp27}, TNode<Map>{tmp0});
    }
    if (catch43__label.is_used()) {
      compiler::CodeAssemblerLabel catch43_skip(&ca_);
      ca_.Goto(&catch43_skip);
      ca_.Bind(&catch43__label, &tmp44);
      ca_.Goto(&block21, phi_bb16_3);
      ca_.Bind(&catch43_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch46__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch46__label);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch46__label.is_used()) {
      compiler::CodeAssemblerLabel catch46_skip(&ca_);
      ca_.Goto(&catch46_skip);
      ca_.Bind(&catch46__label, &tmp47);
      ca_.Goto(&block24, phi_bb16_3);
      ca_.Bind(&catch46_skip);
    }
    tmp48 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{parameter1, tmp45});
    tmp49 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch51__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch51__label);
    tmp50 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp48}, TNode<JSAny>{tmp49}, TNode<JSAny>{tmp42}, TNode<JSAny>{tmp10});
    }
    if (catch51__label.is_used()) {
      compiler::CodeAssemblerLabel catch51_skip(&ca_);
      ca_.Goto(&catch51_skip);
      ca_.Bind(&catch51__label, &tmp52);
      ca_.Goto(&block25, phi_bb16_3);
      ca_.Bind(&catch51_skip);
    }
    compiler::CodeAssemblerLabel label54(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch55__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch55__label);
    tmp53 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp50}, &label54);
    }
    if (catch55__label.is_used()) {
      compiler::CodeAssemblerLabel catch55_skip(&ca_);
      ca_.Goto(&catch55_skip);
      ca_.Bind(&catch55__label, &tmp56);
      ca_.Goto(&block30, phi_bb16_3);
      ca_.Bind(&catch55_skip);
    }
    ca_.Goto(&block28, phi_bb16_3);
    if (label54.is_used()) {
      ca_.Bind(&label54);
      ca_.Goto(&block29, phi_bb16_3);
    }
  }

  TNode<BoolT> phi_bb19_3;
  TNode<Union<JSMessageObject, TheHole>> tmp57;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_3);
    tmp57 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb19_3, tmp36, tmp57);
  }

  TNode<BoolT> phi_bb20_3;
  TNode<Union<JSMessageObject, TheHole>> tmp58;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_3);
    tmp58 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb20_3, tmp41, tmp58);
  }

  TNode<BoolT> phi_bb21_3;
  TNode<Union<JSMessageObject, TheHole>> tmp59;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_3);
    tmp59 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb21_3, tmp44, tmp59);
  }

  TNode<BoolT> phi_bb24_3;
  TNode<Union<JSMessageObject, TheHole>> tmp60;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_3);
    tmp60 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb24_3, tmp47, tmp60);
  }

  TNode<BoolT> phi_bb25_3;
  TNode<Union<JSMessageObject, TheHole>> tmp61;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_3);
    tmp61 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb25_3, tmp52, tmp61);
  }

  TNode<BoolT> phi_bb30_3;
  TNode<Union<JSMessageObject, TheHole>> tmp62;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_3);
    tmp62 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb30_3, tmp56, tmp62);
  }

  TNode<BoolT> phi_bb29_3;
      TNode<JSAny> tmp64;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch63__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch63__label);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), kFlatMapMethodName_0(state_));
    }
    if (catch63__label.is_used()) {
      compiler::CodeAssemblerLabel catch63_skip(&ca_);
      ca_.Bind(&catch63__label, &tmp64);
      ca_.Goto(&block31, phi_bb29_3);
    }
  }

  TNode<BoolT> phi_bb28_3;
  TNode<IntPtrT> tmp65;
      TNode<JSAny> tmp67;
  TNode<JSReceiver> tmp68;
  TNode<JSAny> tmp69;
      TNode<JSAny> tmp71;
  TNode<IntPtrT> tmp72;
      TNode<JSAny> tmp74;
  TNode<IntPtrT> tmp75;
      TNode<JSAny> tmp77;
  TNode<BoolT> tmp78;
      TNode<JSAny> tmp80;
  TNode<IntPtrT> tmp81;
      TNode<JSAny> tmp83;
  TNode<Number> tmp84;
      TNode<JSAny> tmp86;
  TNode<Number> tmp87;
      TNode<JSAny> tmp89;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch66__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch66__label);
    tmp65 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    }
    if (catch66__label.is_used()) {
      compiler::CodeAssemblerLabel catch66_skip(&ca_);
      ca_.Goto(&catch66_skip);
      ca_.Bind(&catch66__label, &tmp67);
      ca_.Goto(&block32, phi_bb28_3);
      ca_.Bind(&catch66_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch70__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch70__label);
    std::tie(tmp68, tmp69) = GetIteratorFlattenable_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, String>>{tmp53}).Flatten();
    }
    if (catch70__label.is_used()) {
      compiler::CodeAssemblerLabel catch70_skip(&ca_);
      ca_.Goto(&catch70_skip);
      ca_.Bind(&catch70__label, &tmp71);
      ca_.Goto(&block33, phi_bb28_3);
      ca_.Bind(&catch70_skip);
    }
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp65}, tmp68);
    compiler::CodeAssemblerExceptionHandlerLabel catch73__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch73__label);
    tmp72 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch73__label.is_used()) {
      compiler::CodeAssemblerLabel catch73_skip(&ca_);
      ca_.Goto(&catch73_skip);
      ca_.Bind(&catch73__label, &tmp74);
      ca_.Goto(&block34, phi_bb28_3);
      ca_.Bind(&catch73_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch76__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch76__label);
    tmp75 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp65}, TNode<IntPtrT>{tmp72});
    }
    if (catch76__label.is_used()) {
      compiler::CodeAssemblerLabel catch76_skip(&ca_);
      ca_.Goto(&catch76_skip);
      ca_.Bind(&catch76__label, &tmp77);
      ca_.Goto(&block35, phi_bb28_3);
      ca_.Bind(&catch76_skip);
    }
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp75}, tmp69);
    compiler::CodeAssemblerExceptionHandlerLabel catch79__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch79__label);
    tmp78 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch79__label.is_used()) {
      compiler::CodeAssemblerLabel catch79_skip(&ca_);
      ca_.Goto(&catch79_skip);
      ca_.Bind(&catch79__label, &tmp80);
      ca_.Goto(&block36, phi_bb28_3);
      ca_.Bind(&catch79_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch82__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch82__label);
    tmp81 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch82__label.is_used()) {
      compiler::CodeAssemblerLabel catch82_skip(&ca_);
      ca_.Goto(&catch82_skip);
      ca_.Bind(&catch82__label, &tmp83);
      ca_.Goto(&block40);
      ca_.Bind(&catch82_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch85__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch85__label);
    tmp84 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch85__label.is_used()) {
      compiler::CodeAssemblerLabel catch85_skip(&ca_);
      ca_.Goto(&catch85_skip);
      ca_.Bind(&catch85__label, &tmp86);
      ca_.Goto(&block41);
      ca_.Bind(&catch85_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch88__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch88__label);
    tmp87 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp10}, TNode<Number>{tmp84});
    }
    if (catch88__label.is_used()) {
      compiler::CodeAssemblerLabel catch88_skip(&ca_);
      ca_.Goto(&catch88_skip);
      ca_.Bind(&catch88__label, &tmp89);
      ca_.Goto(&block42);
      ca_.Bind(&catch88_skip);
    }
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{parameter1, tmp81}, tmp87);
    ca_.Goto(&block9, tmp78);
  }

  TNode<BoolT> phi_bb31_3;
  TNode<Union<JSMessageObject, TheHole>> tmp90;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_3);
    tmp90 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb31_3, tmp64, tmp90);
  }

  TNode<BoolT> phi_bb32_3;
  TNode<Union<JSMessageObject, TheHole>> tmp91;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_3);
    tmp91 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb32_3, tmp67, tmp91);
  }

  TNode<BoolT> phi_bb33_3;
  TNode<Union<JSMessageObject, TheHole>> tmp92;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_3);
    tmp92 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb33_3, tmp71, tmp92);
  }

  TNode<BoolT> phi_bb34_3;
  TNode<Union<JSMessageObject, TheHole>> tmp93;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_3);
    tmp93 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb34_3, tmp74, tmp93);
  }

  TNode<BoolT> phi_bb35_3;
  TNode<Union<JSMessageObject, TheHole>> tmp94;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_3);
    tmp94 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb35_3, tmp77, tmp94);
  }

  TNode<BoolT> phi_bb36_3;
  TNode<Union<JSMessageObject, TheHole>> tmp95;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_3);
    tmp95 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block23, phi_bb36_3, tmp80, tmp95);
  }

  TNode<BoolT> phi_bb23_3;
  TNode<JSAny> phi_bb23_7;
  TNode<Union<JSMessageObject, TheHole>> phi_bb23_8;
  TNode<IntPtrT> tmp96;
      TNode<JSAny> tmp98;
  TNode<JSReceiver> tmp99;
      TNode<JSAny> tmp101;
      TNode<JSAny> tmp103;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_3, &phi_bb23_7, &phi_bb23_8);
    compiler::CodeAssemblerExceptionHandlerLabel catch97__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch97__label);
    tmp96 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch97__label.is_used()) {
      compiler::CodeAssemblerLabel catch97_skip(&ca_);
      ca_.Goto(&catch97_skip);
      ca_.Bind(&catch97__label, &tmp98);
      ca_.Goto(&block37, phi_bb23_3);
      ca_.Bind(&catch97_skip);
    }
    tmp99 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp96});
    compiler::CodeAssemblerExceptionHandlerLabel catch100__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch100__label);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp99});
    }
    if (catch100__label.is_used()) {
      compiler::CodeAssemblerLabel catch100_skip(&ca_);
      ca_.Goto(&catch100_skip);
      ca_.Bind(&catch100__label, &tmp101);
      ca_.Goto(&block38, phi_bb23_3);
      ca_.Bind(&catch100_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch102__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch102__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb23_7, phi_bb23_8);
    CodeStubAssembler(state_).Unreachable();
    }
    if (catch102__label.is_used()) {
      compiler::CodeAssemblerLabel catch102_skip(&ca_);
      ca_.Bind(&catch102__label, &tmp103);
      ca_.Goto(&block39, phi_bb23_3);
    }
  }

  TNode<BoolT> phi_bb37_3;
  TNode<Union<JSMessageObject, TheHole>> tmp104;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_3);
    tmp104 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb37_3, tmp98, tmp104);
  }

  TNode<BoolT> phi_bb38_3;
  TNode<Union<JSMessageObject, TheHole>> tmp105;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_3);
    tmp105 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb38_3, tmp101, tmp105);
  }

  TNode<BoolT> phi_bb39_3;
  TNode<Union<JSMessageObject, TheHole>> tmp106;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_3);
    tmp106 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb39_3, tmp103, tmp106);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp107;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp107 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp78, tmp83, tmp107);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp108;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    tmp108 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp78, tmp86, tmp108);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp109;
  if (block42.is_used()) {
    ca_.Bind(&block42);
    tmp109 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp78, tmp89, tmp109);
  }

  TNode<BoolT> phi_bb9_3;
  TNode<IntPtrT> tmp110;
      TNode<JSAny> tmp112;
  TNode<JSReceiver> tmp113;
  TNode<IntPtrT> tmp114;
      TNode<JSAny> tmp116;
  TNode<IntPtrT> tmp117;
      TNode<JSAny> tmp119;
  TNode<JSAny> tmp120;
  TNode<JSReceiver> tmp121;
      TNode<JSAny> tmp124;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch111__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch111__label);
    tmp110 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    }
    if (catch111__label.is_used()) {
      compiler::CodeAssemblerLabel catch111_skip(&ca_);
      ca_.Goto(&catch111_skip);
      ca_.Bind(&catch111__label, &tmp112);
      ca_.Goto(&block47, phi_bb9_3);
      ca_.Bind(&catch111_skip);
    }
    tmp113 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp110});
    compiler::CodeAssemblerExceptionHandlerLabel catch115__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch115__label);
    tmp114 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch115__label.is_used()) {
      compiler::CodeAssemblerLabel catch115_skip(&ca_);
      ca_.Goto(&catch115_skip);
      ca_.Bind(&catch115__label, &tmp116);
      ca_.Goto(&block48, phi_bb9_3);
      ca_.Bind(&catch115_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch118__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch118__label);
    tmp117 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp110}, TNode<IntPtrT>{tmp114});
    }
    if (catch118__label.is_used()) {
      compiler::CodeAssemblerLabel catch118_skip(&ca_);
      ca_.Goto(&catch118_skip);
      ca_.Bind(&catch118__label, &tmp119);
      ca_.Goto(&block49, phi_bb9_3);
      ca_.Bind(&catch118_skip);
    }
    tmp120 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp117});
    compiler::CodeAssemblerLabel label122(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch123__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch123__label);
    tmp121 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp113}, TNode<JSAny>{tmp120}}, TNode<Map>{tmp0}, &label122);
    }
    if (catch123__label.is_used()) {
      compiler::CodeAssemblerLabel catch123_skip(&ca_);
      ca_.Goto(&catch123_skip);
      ca_.Bind(&catch123__label, &tmp124);
      ca_.Goto(&block52, phi_bb9_3);
      ca_.Bind(&catch123_skip);
    }
    ca_.Goto(&block50, phi_bb9_3);
    if (label122.is_used()) {
      ca_.Bind(&label122);
      ca_.Goto(&block51, phi_bb9_3);
    }
  }

  TNode<BoolT> phi_bb47_3;
  TNode<Union<JSMessageObject, TheHole>> tmp125;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_3);
    tmp125 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb47_3, tmp112, tmp125);
  }

  TNode<BoolT> phi_bb48_3;
  TNode<Union<JSMessageObject, TheHole>> tmp126;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_3);
    tmp126 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb48_3, tmp116, tmp126);
  }

  TNode<BoolT> phi_bb49_3;
  TNode<Union<JSMessageObject, TheHole>> tmp127;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_3);
    tmp127 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb49_3, tmp119, tmp127);
  }

  TNode<BoolT> phi_bb52_3;
  TNode<Union<JSMessageObject, TheHole>> tmp128;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_3);
    tmp128 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb52_3, tmp124, tmp128);
  }

  TNode<BoolT> phi_bb51_3;
  TNode<BoolT> tmp129;
      TNode<JSAny> tmp131;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch130__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch130__label);
    tmp129 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    }
    if (catch130__label.is_used()) {
      compiler::CodeAssemblerLabel catch130_skip(&ca_);
      ca_.Goto(&catch130_skip);
      ca_.Bind(&catch130__label, &tmp131);
      ca_.Goto(&block59, phi_bb51_3);
      ca_.Bind(&catch130_skip);
    }
    ca_.Goto(&block5, tmp129);
  }

  TNode<BoolT> phi_bb50_3;
  TNode<JSAny> tmp132;
      TNode<JSAny> tmp134;
      TNode<JSAny> tmp136;
  TNode<False> tmp137;
  TNode<JSObject> tmp138;
      TNode<JSAny> tmp140;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_3);
    compiler::CodeAssemblerExceptionHandlerLabel catch133__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch133__label);
    tmp132 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp121}, TNode<Map>{tmp0});
    }
    if (catch133__label.is_used()) {
      compiler::CodeAssemblerLabel catch133_skip(&ca_);
      ca_.Goto(&catch133_skip);
      ca_.Bind(&catch133__label, &tmp134);
      ca_.Goto(&block53, phi_bb50_3);
      ca_.Bind(&catch133_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch135__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch135__label);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch135__label.is_used()) {
      compiler::CodeAssemblerLabel catch135_skip(&ca_);
      ca_.Goto(&catch135_skip);
      ca_.Bind(&catch135__label, &tmp136);
      ca_.Goto(&block54, phi_bb50_3);
      ca_.Bind(&catch135_skip);
    }
    tmp137 = False_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch139__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch139__label);
    tmp138 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp132}, TNode<Boolean>{tmp137});
    }
    if (catch139__label.is_used()) {
      compiler::CodeAssemblerLabel catch139_skip(&ca_);
      ca_.Goto(&catch139_skip);
      ca_.Bind(&catch139__label, &tmp140);
      ca_.Goto(&block55, phi_bb50_3);
      ca_.Bind(&catch139_skip);
    }
    CodeStubAssembler(state_).Return(tmp138);
  }

  TNode<BoolT> phi_bb53_3;
  TNode<Union<JSMessageObject, TheHole>> tmp141;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_3);
    tmp141 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb53_3, tmp134, tmp141);
  }

  TNode<BoolT> phi_bb54_3;
  TNode<Union<JSMessageObject, TheHole>> tmp142;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_3);
    tmp142 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb54_3, tmp136, tmp142);
  }

  TNode<BoolT> phi_bb55_3;
  TNode<Union<JSMessageObject, TheHole>> tmp143;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_3);
    tmp143 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block46, phi_bb55_3, tmp140, tmp143);
  }

  TNode<BoolT> phi_bb46_3;
  TNode<JSAny> phi_bb46_5;
  TNode<Union<JSMessageObject, TheHole>> phi_bb46_6;
  TNode<IntPtrT> tmp144;
      TNode<JSAny> tmp146;
  TNode<JSReceiver> tmp147;
      TNode<JSAny> tmp149;
      TNode<JSAny> tmp151;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_3, &phi_bb46_5, &phi_bb46_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch145__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch145__label);
    tmp144 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch145__label.is_used()) {
      compiler::CodeAssemblerLabel catch145_skip(&ca_);
      ca_.Goto(&catch145_skip);
      ca_.Bind(&catch145__label, &tmp146);
      ca_.Goto(&block56, phi_bb46_3);
      ca_.Bind(&catch145_skip);
    }
    tmp147 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp144});
    compiler::CodeAssemblerExceptionHandlerLabel catch148__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch148__label);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp147});
    }
    if (catch148__label.is_used()) {
      compiler::CodeAssemblerLabel catch148_skip(&ca_);
      ca_.Goto(&catch148_skip);
      ca_.Bind(&catch148__label, &tmp149);
      ca_.Goto(&block57, phi_bb46_3);
      ca_.Bind(&catch148_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch150__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch150__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb46_5, phi_bb46_6);
    CodeStubAssembler(state_).Unreachable();
    }
    if (catch150__label.is_used()) {
      compiler::CodeAssemblerLabel catch150_skip(&ca_);
      ca_.Bind(&catch150__label, &tmp151);
      ca_.Goto(&block58, phi_bb46_3);
    }
  }

  TNode<BoolT> phi_bb56_3;
  TNode<Union<JSMessageObject, TheHole>> tmp152;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_3);
    tmp152 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb56_3, tmp146, tmp152);
  }

  TNode<BoolT> phi_bb57_3;
  TNode<Union<JSMessageObject, TheHole>> tmp153;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_3);
    tmp153 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb57_3, tmp149, tmp153);
  }

  TNode<BoolT> phi_bb58_3;
  TNode<Union<JSMessageObject, TheHole>> tmp154;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_3);
    tmp154 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb58_3, tmp151, tmp154);
  }

  TNode<BoolT> phi_bb59_3;
  TNode<Union<JSMessageObject, TheHole>> tmp155;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_3);
    tmp155 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb59_3, tmp131, tmp155);
  }

  TNode<BoolT> phi_bb4_3;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:815:3");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb2_3;
  TNode<JSAny> phi_bb2_4;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_5;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4, &phi_bb2_5);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb2_4, phi_bb2_5);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeReduce, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, JSAny, Number> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, JSAny, Number> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, JSAny, Number> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, JSAny, Number> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, JSAny, Number> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Number, JSAny, Number> block27(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Number> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block29(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Number, JSAny, Union<JSMessageObject, TheHole>> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, JSAny, Number> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.reduce");
  }

  TNode<IntPtrT> tmp2;
  TNode<JSAny> tmp3;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp2});
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp3}, &label5);
    ca_.Goto(&block9);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, tmp3);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp6;
  TNode<JSAny> tmp7;
  TNode<Map> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp6, tmp7) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp8 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    tmp9 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp10 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp9});
    ca_.Branch(tmp10, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<JSReceiver> tmp11;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label12(&ca_);
    tmp11 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp6}, TNode<JSAny>{tmp7}}, TNode<Map>{tmp8}, &label12);
    ca_.Goto(&block16);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block17);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIteratorReduceNoInitial), "Iterator.prototype.reduce");
  }

  TNode<JSAny> tmp13;
  TNode<Number> tmp14;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp13 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp11}, TNode<Map>{tmp8});
    tmp14 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    ca_.Goto(&block13, tmp11, tmp13, tmp14);
  }

  TNode<IntPtrT> tmp15;
  TNode<JSAny> tmp16;
  TNode<Number> tmp17;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp15 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp16 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp15});
    tmp17 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block13, ca_.Uninitialized<JSReceiver>(), tmp16, tmp17);
  }

  TNode<JSReceiver> phi_bb13_11;
  TNode<JSAny> phi_bb13_12;
  TNode<Number> phi_bb13_13;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_11, &phi_bb13_12, &phi_bb13_13);
    ca_.Goto(&block20, phi_bb13_11, phi_bb13_12, phi_bb13_13);
  }

  TNode<JSReceiver> phi_bb20_11;
  TNode<JSAny> phi_bb20_12;
  TNode<Number> phi_bb20_13;
  TNode<BoolT> tmp18;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_11, &phi_bb20_12, &phi_bb20_13);
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp18, &block18, std::vector<compiler::Node*>{phi_bb20_11, phi_bb20_12, phi_bb20_13}, &block19, std::vector<compiler::Node*>{phi_bb20_11, phi_bb20_12, phi_bb20_13});
  }

  TNode<JSReceiver> phi_bb18_11;
  TNode<JSAny> phi_bb18_12;
  TNode<Number> phi_bb18_13;
  TNode<JSReceiver> tmp19;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_11, &phi_bb18_12, &phi_bb18_13);
    compiler::CodeAssemblerLabel label20(&ca_);
    tmp19 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp6}, TNode<JSAny>{tmp7}}, TNode<Map>{tmp8}, &label20);
    ca_.Goto(&block23, phi_bb18_11, phi_bb18_12, phi_bb18_13);
    if (label20.is_used()) {
      ca_.Bind(&label20);
      ca_.Goto(&block24, phi_bb18_11, phi_bb18_12, phi_bb18_13);
    }
  }

  TNode<JSReceiver> phi_bb24_11;
  TNode<JSAny> phi_bb24_12;
  TNode<Number> phi_bb24_13;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_11, &phi_bb24_12, &phi_bb24_13);
    arguments.PopAndReturn(phi_bb24_12);
  }

  TNode<JSReceiver> phi_bb23_11;
  TNode<JSAny> phi_bb23_12;
  TNode<Number> phi_bb23_13;
  TNode<JSAny> tmp21;
  TNode<Undefined> tmp22;
  TNode<JSAny> tmp23;
      TNode<JSAny> tmp25;
  TNode<Number> tmp26;
      TNode<JSAny> tmp28;
  TNode<Number> tmp29;
      TNode<JSAny> tmp31;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_11, &phi_bb23_12, &phi_bb23_13);
    tmp21 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp19}, TNode<Map>{tmp8});
    tmp22 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch24__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch24__label);
    tmp23 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp4}, TNode<JSAny>{tmp22}, TNode<JSAny>{phi_bb23_12}, TNode<JSAny>{tmp21}, TNode<JSAny>{phi_bb23_13});
    }
    if (catch24__label.is_used()) {
      compiler::CodeAssemblerLabel catch24_skip(&ca_);
      ca_.Goto(&catch24_skip);
      ca_.Bind(&catch24__label, &tmp25);
      ca_.Goto(&block27, phi_bb23_12, phi_bb23_13, phi_bb23_12, phi_bb23_13);
      ca_.Bind(&catch24_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch27__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch27__label);
    tmp26 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch27__label.is_used()) {
      compiler::CodeAssemblerLabel catch27_skip(&ca_);
      ca_.Goto(&catch27_skip);
      ca_.Bind(&catch27__label, &tmp28);
      ca_.Goto(&block28, phi_bb23_13, phi_bb23_13, phi_bb23_13);
      ca_.Bind(&catch27_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch30__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch30__label);
    tmp29 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb23_13}, TNode<Number>{tmp26});
    }
    if (catch30__label.is_used()) {
      compiler::CodeAssemblerLabel catch30_skip(&ca_);
      ca_.Goto(&catch30_skip);
      ca_.Bind(&catch30__label, &tmp31);
      ca_.Goto(&block29, phi_bb23_13, phi_bb23_13);
      ca_.Bind(&catch30_skip);
    }
    ca_.Goto(&block20, tmp19, tmp23, tmp29);
  }

  TNode<JSAny> phi_bb27_12;
  TNode<Number> phi_bb27_13;
  TNode<JSAny> phi_bb27_18;
  TNode<Number> phi_bb27_20;
  TNode<Union<JSMessageObject, TheHole>> tmp32;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_12, &phi_bb27_13, &phi_bb27_18, &phi_bb27_20);
    tmp32 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block26, phi_bb27_12, phi_bb27_13, tmp25, tmp32);
  }

  TNode<Number> phi_bb28_13;
  TNode<Number> phi_bb28_16;
  TNode<Number> phi_bb28_17;
  TNode<Union<JSMessageObject, TheHole>> tmp33;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_13, &phi_bb28_16, &phi_bb28_17);
    tmp33 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block26, tmp23, phi_bb28_13, tmp28, tmp33);
  }

  TNode<Number> phi_bb29_13;
  TNode<Number> phi_bb29_16;
  TNode<Union<JSMessageObject, TheHole>> tmp34;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_13, &phi_bb29_16);
    tmp34 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block26, tmp23, phi_bb29_13, tmp31, tmp34);
  }

  TNode<JSAny> phi_bb26_12;
  TNode<Number> phi_bb26_13;
  TNode<JSAny> phi_bb26_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb26_16;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_12, &phi_bb26_13, &phi_bb26_15, &phi_bb26_16);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb26_15, phi_bb26_16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> phi_bb19_11;
  TNode<JSAny> phi_bb19_12;
  TNode<Number> phi_bb19_13;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_11, &phi_bb19_12, &phi_bb19_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:906:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeToArray, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver, IntPtrT, IntPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver, IntPtrT, IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver, IntPtrT, IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver, IntPtrT, IntPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver, IntPtrT, IntPtrT> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver, IntPtrT, IntPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSReceiver> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.toArray");
  }

  TNode<JSReceiver> tmp2;
  TNode<JSAny> tmp3;
  TNode<FixedArray> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Map> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    std::tie(tmp2, tmp3) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    std::tie(tmp4, tmp5, tmp6) = NewGrowableFixedArray_0(state_).Flatten();
    tmp7 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block7, tmp4, tmp5, tmp6, ca_.Uninitialized<JSReceiver>());
  }

  TNode<FixedArray> phi_bb7_5;
  TNode<IntPtrT> phi_bb7_6;
  TNode<IntPtrT> phi_bb7_7;
  TNode<JSReceiver> phi_bb7_9;
  TNode<BoolT> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5, &phi_bb7_6, &phi_bb7_7, &phi_bb7_9);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp8, &block5, std::vector<compiler::Node*>{phi_bb7_5, phi_bb7_6, phi_bb7_7, phi_bb7_9}, &block6, std::vector<compiler::Node*>{phi_bb7_5, phi_bb7_6, phi_bb7_7, phi_bb7_9});
  }

  TNode<FixedArray> phi_bb5_5;
  TNode<IntPtrT> phi_bb5_6;
  TNode<IntPtrT> phi_bb5_7;
  TNode<JSReceiver> phi_bb5_9;
  TNode<JSReceiver> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5, &phi_bb5_6, &phi_bb5_7, &phi_bb5_9);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp2}, TNode<JSAny>{tmp3}}, TNode<Map>{tmp7}, &label10);
    ca_.Goto(&block10, phi_bb5_5, phi_bb5_6, phi_bb5_7, phi_bb5_9);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block11, phi_bb5_5, phi_bb5_6, phi_bb5_7, phi_bb5_9);
    }
  }

  TNode<FixedArray> phi_bb11_5;
  TNode<IntPtrT> phi_bb11_6;
  TNode<IntPtrT> phi_bb11_7;
  TNode<JSReceiver> phi_bb11_9;
  TNode<NativeContext> tmp11;
  TNode<Map> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_5, &phi_bb11_6, &phi_bb11_7, &phi_bb11_9);
    tmp11 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp12 = CodeStubAssembler(state_).LoadJSArrayElementsMap(CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_ELEMENTS), TNode<NativeContext>{tmp11});
    tmp13 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp14 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb11_7}, TNode<IntPtrT>{tmp13});
    ca_.Branch(tmp14, &block14, std::vector<compiler::Node*>{phi_bb11_5, phi_bb11_6, phi_bb11_7, phi_bb11_9, phi_bb11_7, phi_bb11_7}, &block15, std::vector<compiler::Node*>{phi_bb11_5, phi_bb11_6, phi_bb11_7, phi_bb11_9, phi_bb11_7, phi_bb11_7});
  }

  TNode<FixedArray> phi_bb10_5;
  TNode<IntPtrT> phi_bb10_6;
  TNode<IntPtrT> phi_bb10_7;
  TNode<JSReceiver> phi_bb10_9;
  TNode<JSAny> tmp15;
  TNode<BoolT> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_5, &phi_bb10_6, &phi_bb10_7, &phi_bb10_9);
    tmp15 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp9}, TNode<Map>{tmp7});
    tmp16 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb10_7}, TNode<IntPtrT>{phi_bb10_6});
    ca_.Branch(tmp16, &block22, std::vector<compiler::Node*>{phi_bb10_5, phi_bb10_6, phi_bb10_7}, &block23, std::vector<compiler::Node*>{phi_bb10_5, phi_bb10_6, phi_bb10_7});
  }

  TNode<FixedArray> phi_bb15_5;
  TNode<IntPtrT> phi_bb15_6;
  TNode<IntPtrT> phi_bb15_7;
  TNode<JSReceiver> phi_bb15_9;
  TNode<IntPtrT> phi_bb15_14;
  TNode<IntPtrT> phi_bb15_15;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_5, &phi_bb15_6, &phi_bb15_7, &phi_bb15_9, &phi_bb15_14, &phi_bb15_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb14_5;
  TNode<IntPtrT> phi_bb14_6;
  TNode<IntPtrT> phi_bb14_7;
  TNode<JSReceiver> phi_bb14_9;
  TNode<IntPtrT> phi_bb14_14;
  TNode<IntPtrT> phi_bb14_15;
  TNode<IntPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_5, &phi_bb14_6, &phi_bb14_7, &phi_bb14_9, &phi_bb14_14, &phi_bb14_15);
    tmp17 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp18 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb14_15}, TNode<IntPtrT>{tmp17});
    ca_.Branch(tmp18, &block16, std::vector<compiler::Node*>{phi_bb14_5, phi_bb14_6, phi_bb14_7, phi_bb14_9, phi_bb14_14, phi_bb14_15}, &block17, std::vector<compiler::Node*>{phi_bb14_5, phi_bb14_6, phi_bb14_7, phi_bb14_9, phi_bb14_14, phi_bb14_15});
  }

  TNode<FixedArray> phi_bb17_5;
  TNode<IntPtrT> phi_bb17_6;
  TNode<IntPtrT> phi_bb17_7;
  TNode<JSReceiver> phi_bb17_9;
  TNode<IntPtrT> phi_bb17_14;
  TNode<IntPtrT> phi_bb17_15;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_5, &phi_bb17_6, &phi_bb17_7, &phi_bb17_9, &phi_bb17_14, &phi_bb17_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb16_5;
  TNode<IntPtrT> phi_bb16_6;
  TNode<IntPtrT> phi_bb16_7;
  TNode<JSReceiver> phi_bb16_9;
  TNode<IntPtrT> phi_bb16_14;
  TNode<IntPtrT> phi_bb16_15;
  TNode<BoolT> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_5, &phi_bb16_6, &phi_bb16_7, &phi_bb16_9, &phi_bb16_14, &phi_bb16_15);
    tmp19 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb16_15}, TNode<IntPtrT>{phi_bb16_7});
    ca_.Branch(tmp19, &block18, std::vector<compiler::Node*>{phi_bb16_5, phi_bb16_6, phi_bb16_7, phi_bb16_9, phi_bb16_14, phi_bb16_15}, &block19, std::vector<compiler::Node*>{phi_bb16_5, phi_bb16_6, phi_bb16_7, phi_bb16_9, phi_bb16_14, phi_bb16_15});
  }

  TNode<FixedArray> phi_bb19_5;
  TNode<IntPtrT> phi_bb19_6;
  TNode<IntPtrT> phi_bb19_7;
  TNode<JSReceiver> phi_bb19_9;
  TNode<IntPtrT> phi_bb19_14;
  TNode<IntPtrT> phi_bb19_15;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_5, &phi_bb19_6, &phi_bb19_7, &phi_bb19_9, &phi_bb19_14, &phi_bb19_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb18_5;
  TNode<IntPtrT> phi_bb18_6;
  TNode<IntPtrT> phi_bb18_7;
  TNode<JSReceiver> phi_bb18_9;
  TNode<IntPtrT> phi_bb18_14;
  TNode<IntPtrT> phi_bb18_15;
  TNode<IntPtrT> tmp20;
  TNode<TheHole> tmp21;
  TNode<FixedArray> tmp22;
  TNode<Smi> tmp23;
  TNode<JSArray> tmp24;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_5, &phi_bb18_6, &phi_bb18_7, &phi_bb18_9, &phi_bb18_14, &phi_bb18_15);
    tmp20 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp21 = TheHole_0(state_);
    tmp22 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb18_5}, TNode<IntPtrT>{tmp20}, TNode<IntPtrT>{phi_bb18_7}, TNode<IntPtrT>{phi_bb18_15}, TNode<Hole>{tmp21});
    tmp23 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb18_7});
    tmp24 = CodeStubAssembler(state_).AllocateJSArray(TNode<Map>{tmp12}, TNode<FixedArrayBase>{tmp22}, TNode<Smi>{tmp23});
    CodeStubAssembler(state_).Return(tmp24);
  }

  TNode<FixedArray> phi_bb23_5;
  TNode<IntPtrT> phi_bb23_6;
  TNode<IntPtrT> phi_bb23_7;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_5, &phi_bb23_6, &phi_bb23_7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb22_5;
  TNode<IntPtrT> phi_bb22_6;
  TNode<IntPtrT> phi_bb22_7;
  TNode<BoolT> tmp25;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_5, &phi_bb22_6, &phi_bb22_7);
    tmp25 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb22_6}, TNode<IntPtrT>{phi_bb22_7});
    ca_.Branch(tmp25, &block24, std::vector<compiler::Node*>{phi_bb22_5, phi_bb22_6, phi_bb22_7}, &block25, std::vector<compiler::Node*>{phi_bb22_5, phi_bb22_6, phi_bb22_7});
  }

  TNode<FixedArray> phi_bb24_5;
  TNode<IntPtrT> phi_bb24_6;
  TNode<IntPtrT> phi_bb24_7;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<BoolT> tmp32;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_5, &phi_bb24_6, &phi_bb24_7);
    tmp26 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp27 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb24_6}, TNode<IntPtrT>{tmp26});
    tmp28 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb24_6}, TNode<IntPtrT>{tmp27});
    tmp29 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp30 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp29});
    tmp31 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp32 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb24_7}, TNode<IntPtrT>{tmp31});
    ca_.Branch(tmp32, &block27, std::vector<compiler::Node*>{phi_bb24_5, phi_bb24_7}, &block28, std::vector<compiler::Node*>{phi_bb24_5, phi_bb24_7});
  }

  TNode<FixedArray> phi_bb28_5;
  TNode<IntPtrT> phi_bb28_7;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_5, &phi_bb28_7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb27_5;
  TNode<IntPtrT> phi_bb27_7;
  TNode<IntPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_5, &phi_bb27_7);
    tmp33 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp34 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp30}, TNode<IntPtrT>{tmp33});
    ca_.Branch(tmp34, &block29, std::vector<compiler::Node*>{phi_bb27_5, phi_bb27_7}, &block30, std::vector<compiler::Node*>{phi_bb27_5, phi_bb27_7});
  }

  TNode<FixedArray> phi_bb30_5;
  TNode<IntPtrT> phi_bb30_7;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_5, &phi_bb30_7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb29_5;
  TNode<IntPtrT> phi_bb29_7;
  TNode<BoolT> tmp35;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_5, &phi_bb29_7);
    tmp35 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp30}, TNode<IntPtrT>{phi_bb29_7});
    ca_.Branch(tmp35, &block31, std::vector<compiler::Node*>{phi_bb29_5, phi_bb29_7}, &block32, std::vector<compiler::Node*>{phi_bb29_5, phi_bb29_7});
  }

  TNode<FixedArray> phi_bb32_5;
  TNode<IntPtrT> phi_bb32_7;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_5, &phi_bb32_7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb31_5;
  TNode<IntPtrT> phi_bb31_7;
  TNode<IntPtrT> tmp36;
  TNode<TheHole> tmp37;
  TNode<FixedArray> tmp38;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_5, &phi_bb31_7);
    tmp36 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp37 = TheHole_0(state_);
    tmp38 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb31_5}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{phi_bb31_7}, TNode<IntPtrT>{tmp30}, TNode<Hole>{tmp37});
    ca_.Goto(&block25, tmp38, tmp30, phi_bb31_7);
  }

  TNode<FixedArray> phi_bb25_5;
  TNode<IntPtrT> phi_bb25_6;
  TNode<IntPtrT> phi_bb25_7;
  TNode<Union<HeapObject, TaggedIndex>> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<UintPtrT> tmp44;
  TNode<UintPtrT> tmp45;
  TNode<BoolT> tmp46;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_5, &phi_bb25_6, &phi_bb25_7);
    std::tie(tmp39, tmp40, tmp41) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb25_5}).Flatten();
    tmp42 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp43 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb25_7}, TNode<IntPtrT>{tmp42});
    tmp44 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb25_7});
    tmp45 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp41});
    tmp46 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp44}, TNode<UintPtrT>{tmp45});
    ca_.Branch(tmp46, &block37, std::vector<compiler::Node*>{phi_bb25_5, phi_bb25_6, phi_bb25_5, phi_bb25_7, phi_bb25_7, phi_bb25_7, phi_bb25_7}, &block38, std::vector<compiler::Node*>{phi_bb25_5, phi_bb25_6, phi_bb25_5, phi_bb25_7, phi_bb25_7, phi_bb25_7, phi_bb25_7});
  }

  TNode<FixedArray> phi_bb37_5;
  TNode<IntPtrT> phi_bb37_6;
  TNode<FixedArray> phi_bb37_13;
  TNode<IntPtrT> phi_bb37_17;
  TNode<IntPtrT> phi_bb37_18;
  TNode<IntPtrT> phi_bb37_22;
  TNode<IntPtrT> phi_bb37_23;
  TNode<IntPtrT> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<Union<HeapObject, TaggedIndex>> tmp49;
  TNode<IntPtrT> tmp50;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_5, &phi_bb37_6, &phi_bb37_13, &phi_bb37_17, &phi_bb37_18, &phi_bb37_22, &phi_bb37_23);
    tmp47 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb37_23});
    tmp48 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp40}, TNode<IntPtrT>{tmp47});
    std::tie(tmp49, tmp50) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp39}, TNode<IntPtrT>{tmp48}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp49, tmp50}, tmp15);
    ca_.Goto(&block7, phi_bb37_5, phi_bb37_6, tmp43, tmp9);
  }

  TNode<FixedArray> phi_bb38_5;
  TNode<IntPtrT> phi_bb38_6;
  TNode<FixedArray> phi_bb38_13;
  TNode<IntPtrT> phi_bb38_17;
  TNode<IntPtrT> phi_bb38_18;
  TNode<IntPtrT> phi_bb38_22;
  TNode<IntPtrT> phi_bb38_23;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_5, &phi_bb38_6, &phi_bb38_13, &phi_bb38_17, &phi_bb38_18, &phi_bb38_22, &phi_bb38_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb6_5;
  TNode<IntPtrT> phi_bb6_6;
  TNode<IntPtrT> phi_bb6_7;
  TNode<JSReceiver> phi_bb6_9;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5, &phi_bb6_6, &phi_bb6_7, &phi_bb6_9);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:947:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeForEach, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kFn);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Number> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, JSAny, Union<JSMessageObject, TheHole>> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.forEach");
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, parameter2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<Number> tmp6;
  TNode<Map> tmp7;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block13, tmp6);
  }

  TNode<Number> phi_bb13_7;
  TNode<BoolT> tmp8;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{phi_bb13_7}, &block12, std::vector<compiler::Node*>{phi_bb13_7});
  }

  TNode<Number> phi_bb11_7;
  TNode<JSReceiver> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Map>{tmp7}, &label10);
    ca_.Goto(&block16, phi_bb11_7);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block17, phi_bb11_7);
    }
  }

  TNode<Number> phi_bb17_7;
  TNode<Undefined> tmp11;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    tmp11 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<Number> phi_bb16_7;
  TNode<JSAny> tmp12;
  TNode<Undefined> tmp13;
  TNode<JSAny> tmp14;
      TNode<JSAny> tmp16;
  TNode<Number> tmp17;
      TNode<JSAny> tmp19;
  TNode<Number> tmp20;
      TNode<JSAny> tmp22;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_7);
    tmp12 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp9}, TNode<Map>{tmp7});
    tmp13 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp2}, TNode<JSAny>{tmp13}, TNode<JSAny>{tmp12}, TNode<JSAny>{phi_bb16_7});
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block20, phi_bb16_7, phi_bb16_7);
      ca_.Bind(&catch15_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch18__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch18__label);
    tmp17 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch18__label.is_used()) {
      compiler::CodeAssemblerLabel catch18_skip(&ca_);
      ca_.Goto(&catch18_skip);
      ca_.Bind(&catch18__label, &tmp19);
      ca_.Goto(&block21, phi_bb16_7, phi_bb16_7, phi_bb16_7);
      ca_.Bind(&catch18_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch21__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch21__label);
    tmp20 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb16_7}, TNode<Number>{tmp17});
    }
    if (catch21__label.is_used()) {
      compiler::CodeAssemblerLabel catch21_skip(&ca_);
      ca_.Goto(&catch21_skip);
      ca_.Bind(&catch21__label, &tmp22);
      ca_.Goto(&block22, phi_bb16_7, phi_bb16_7);
      ca_.Bind(&catch21_skip);
    }
    ca_.Goto(&block13, tmp20);
  }

  TNode<Number> phi_bb20_7;
  TNode<Number> phi_bb20_15;
  TNode<Union<JSMessageObject, TheHole>> tmp23;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7, &phi_bb20_15);
    tmp23 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block19, phi_bb20_7, tmp16, tmp23);
  }

  TNode<Number> phi_bb21_7;
  TNode<Number> phi_bb21_11;
  TNode<Number> phi_bb21_12;
  TNode<Union<JSMessageObject, TheHole>> tmp24;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7, &phi_bb21_11, &phi_bb21_12);
    tmp24 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block19, phi_bb21_7, tmp19, tmp24);
  }

  TNode<Number> phi_bb22_7;
  TNode<Number> phi_bb22_11;
  TNode<Union<JSMessageObject, TheHole>> tmp25;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7, &phi_bb22_11);
    tmp25 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block19, phi_bb22_7, tmp22, tmp25);
  }

  TNode<Number> phi_bb19_7;
  TNode<JSAny> phi_bb19_11;
  TNode<Union<JSMessageObject, TheHole>> phi_bb19_12;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_7, &phi_bb19_11, &phi_bb19_12);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb19_11, phi_bb19_12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> phi_bb12_7;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1012:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeSome, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kPredicate);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.some");
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, parameter2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<Number> tmp6;
  TNode<Map> tmp7;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block13, tmp6);
  }

  TNode<Number> phi_bb13_7;
  TNode<BoolT> tmp8;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{phi_bb13_7}, &block12, std::vector<compiler::Node*>{phi_bb13_7});
  }

  TNode<Number> phi_bb11_7;
  TNode<JSReceiver> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Map>{tmp7}, &label10);
    ca_.Goto(&block16, phi_bb11_7);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block17, phi_bb11_7);
    }
  }

  TNode<Number> phi_bb17_7;
  TNode<False> tmp11;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    tmp11 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<Number> phi_bb16_7;
  TNode<JSAny> tmp12;
  TNode<Undefined> tmp13;
  TNode<JSAny> tmp14;
      TNode<JSAny> tmp16;
  TNode<BoolT> tmp17;
  TNode<BoolT> tmp18;
  TNode<BoolT> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_7);
    tmp12 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp9}, TNode<Map>{tmp7});
    tmp13 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp2}, TNode<JSAny>{tmp13}, TNode<JSAny>{tmp12}, TNode<JSAny>{phi_bb16_7});
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block20, phi_bb16_7, phi_bb16_7);
      ca_.Bind(&catch15_skip);
    }
    tmp17 = ToBoolean_0(state_, TNode<JSAny>{tmp14});
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp19 = CodeStubAssembler(state_).Word32Equal(TNode<BoolT>{tmp17}, TNode<BoolT>{tmp18});
    ca_.Branch(tmp19, &block21, std::vector<compiler::Node*>{phi_bb16_7}, &block22, std::vector<compiler::Node*>{phi_bb16_7});
  }

  TNode<Number> phi_bb20_7;
  TNode<Number> phi_bb20_16;
  TNode<Union<JSMessageObject, TheHole>> tmp20;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7, &phi_bb20_16);
    tmp20 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp16, tmp20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> phi_bb21_7;
  TNode<True> tmp21;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}});
    tmp21 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp21);
  }

  TNode<Number> phi_bb22_7;
  TNode<Number> tmp22;
  TNode<Number> tmp23;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7);
    tmp22 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp23 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb22_7}, TNode<Number>{tmp22});
    ca_.Goto(&block13, tmp23);
  }

  TNode<Number> phi_bb12_7;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1087:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeEvery, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kPredicate);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.every");
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, parameter2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<Number> tmp6;
  TNode<Map> tmp7;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block13, tmp6);
  }

  TNode<Number> phi_bb13_7;
  TNode<BoolT> tmp8;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{phi_bb13_7}, &block12, std::vector<compiler::Node*>{phi_bb13_7});
  }

  TNode<Number> phi_bb11_7;
  TNode<JSReceiver> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Map>{tmp7}, &label10);
    ca_.Goto(&block16, phi_bb11_7);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block17, phi_bb11_7);
    }
  }

  TNode<Number> phi_bb17_7;
  TNode<True> tmp11;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    tmp11 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<Number> phi_bb16_7;
  TNode<JSAny> tmp12;
  TNode<Undefined> tmp13;
  TNode<JSAny> tmp14;
      TNode<JSAny> tmp16;
  TNode<BoolT> tmp17;
  TNode<BoolT> tmp18;
  TNode<BoolT> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_7);
    tmp12 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp9}, TNode<Map>{tmp7});
    tmp13 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp2}, TNode<JSAny>{tmp13}, TNode<JSAny>{tmp12}, TNode<JSAny>{phi_bb16_7});
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block20, phi_bb16_7, phi_bb16_7);
      ca_.Bind(&catch15_skip);
    }
    tmp17 = ToBoolean_0(state_, TNode<JSAny>{tmp14});
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp19 = CodeStubAssembler(state_).Word32Equal(TNode<BoolT>{tmp17}, TNode<BoolT>{tmp18});
    ca_.Branch(tmp19, &block21, std::vector<compiler::Node*>{phi_bb16_7}, &block22, std::vector<compiler::Node*>{phi_bb16_7});
  }

  TNode<Number> phi_bb20_7;
  TNode<Number> phi_bb20_16;
  TNode<Union<JSMessageObject, TheHole>> tmp20;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7, &phi_bb20_16);
    tmp20 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp16, tmp20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> phi_bb21_7;
  TNode<False> tmp21;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}});
    tmp21 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp21);
  }

  TNode<Number> phi_bb22_7;
  TNode<Number> tmp22;
  TNode<Number> tmp23;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7);
    tmp22 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp23 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb22_7}, TNode<Number>{tmp22});
    ca_.Goto(&block13, tmp23);
  }

  TNode<Number> phi_bb12_7;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1162:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeFind, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kPredicate);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.find");
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block9);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, parameter2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  TNode<JSAny> tmp5;
  TNode<Number> tmp6;
  TNode<Map> tmp7;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    std::tie(tmp4, tmp5) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp6 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block13, tmp6);
  }

  TNode<Number> phi_bb13_7;
  TNode<BoolT> tmp8;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{phi_bb13_7}, &block12, std::vector<compiler::Node*>{phi_bb13_7});
  }

  TNode<Number> phi_bb11_7;
  TNode<JSReceiver> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}}, TNode<Map>{tmp7}, &label10);
    ca_.Goto(&block16, phi_bb11_7);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block17, phi_bb11_7);
    }
  }

  TNode<Number> phi_bb17_7;
  TNode<Undefined> tmp11;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    tmp11 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<Number> phi_bb16_7;
  TNode<JSAny> tmp12;
  TNode<Undefined> tmp13;
  TNode<JSAny> tmp14;
      TNode<JSAny> tmp16;
  TNode<BoolT> tmp17;
  TNode<BoolT> tmp18;
  TNode<BoolT> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_7);
    tmp12 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp9}, TNode<Map>{tmp7});
    tmp13 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp2}, TNode<JSAny>{tmp13}, TNode<JSAny>{tmp12}, TNode<JSAny>{phi_bb16_7});
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block20, phi_bb16_7, phi_bb16_7);
      ca_.Bind(&catch15_skip);
    }
    tmp17 = ToBoolean_0(state_, TNode<JSAny>{tmp14});
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp19 = CodeStubAssembler(state_).Word32Equal(TNode<BoolT>{tmp17}, TNode<BoolT>{tmp18});
    ca_.Branch(tmp19, &block21, std::vector<compiler::Node*>{phi_bb16_7}, &block22, std::vector<compiler::Node*>{phi_bb16_7});
  }

  TNode<Number> phi_bb20_7;
  TNode<Number> phi_bb20_16;
  TNode<Union<JSMessageObject, TheHole>> tmp20;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7, &phi_bb20_16);
    tmp20 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp16, tmp20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> phi_bb21_7;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp4}, TNode<JSAny>{tmp5}});
    CodeStubAssembler(state_).Return(tmp12);
  }

  TNode<Number> phi_bb22_7;
  TNode<Number> tmp21;
  TNode<Number> tmp22;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7);
    tmp21 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp22 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb22_7}, TNode<Number>{tmp21});
    ca_.Goto(&block13, tmp22);
  }

  TNode<Number> phi_bb12_7;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1236:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1241&c=1
const char* kConcatMethodName_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return "Iterator.concat";}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1243&c=1
TNode<JSIteratorConcatHelper> NewJSIteratorConcatHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterables) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{p_iterables, tmp0});
    tmp2 = FromConstexpr_uint32_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp3 = CodeStubAssembler(state_).Uint32Mod(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp2});
    tmp4 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp3}, TNode<Uint32T>{tmp4});
    ca_.Branch(tmp5, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1245});
      CodeStubAssembler(state_).FailAssert("Torque assert 'iterables.length % kIteratorRecordFieldCount == 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<Union<HeapObject, TaggedIndex>> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<FixedArray> tmp10;
  TNode<FixedArray> tmp11;
  TNode<Uint32T> tmp12;
  TNode<Smi> tmp13;
  TNode<JSObject> tmp14;
  TNode<Undefined> tmp15;
  TNode<Smi> tmp16;
  TNode<BoolT> tmp17;
  TNode<BoolT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<HeapObject> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<JSIteratorConcatHelper> tmp30;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp6 = ITERATOR_CONCAT_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp7, tmp8) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp6}).Flatten();
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp7, tmp8});
    tmp10 = CodeStubAssembler(state_).EmptyFixedArrayConstant();
    tmp11 = CodeStubAssembler(state_).EmptyFixedArrayConstant();
    tmp12 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp13 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp12});
    tmp14 = GetIteratorPrototype_0(state_, TNode<Context>{p_context});
    tmp15 = Undefined_0(state_);
    tmp16 = SmiConstant_0(state_, IntegerLiteral(false, 0x0ull));
    tmp17 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp20 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp19}, TNode<Map>{tmp9}, TNode<BoolT>{tmp17}, TNode<BoolT>{tmp18});
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp20, tmp21}, tmp9);
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp20, tmp22}, tmp10);
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp20, tmp23}, tmp11);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp20, tmp24}, tmp13);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp20, tmp25}, tmp14);
    tmp26 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp27 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp26});
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp20, tmp27}, tmp15);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp20, tmp28}, p_iterables);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp20, tmp29}, tmp16);
    tmp30 = TORQUE_CAST(TNode<HeapObject>{tmp20});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSIteratorConcatHelper>{tmp30};
}

TF_BUILTIN(IteratorConcat, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<FixedArray> tmp2;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = kEmptyFixedArray_0(state_);
    ca_.Goto(&block3, tmp2);
  }

  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<FixedArray> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp4 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{torque_arguments.length});
    tmp5 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp4});
    ca_.Goto(&block3, tmp5);
  }

  TNode<FixedArray> phi_bb3_6;
  TNode<IntPtrT> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_6);
    tmp6 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block7, tmp6);
  }

  TNode<IntPtrT> phi_bb7_7;
  TNode<BoolT> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_7);
    tmp7 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb7_7}, TNode<IntPtrT>{torque_arguments.length});
    ca_.Branch(tmp7, &block5, std::vector<compiler::Node*>{phi_bb7_7}, &block6, std::vector<compiler::Node*>{phi_bb7_7});
  }

  TNode<IntPtrT> phi_bb5_7;
  TNode<JSAny> tmp8;
  TNode<BoolT> tmp9;
  TNode<BoolT> tmp10;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_7);
    tmp8 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{phi_bb5_7});
    tmp9 = Is_JSReceiver_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp8});
    tmp10 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp9});
    ca_.Branch(tmp10, &block9, std::vector<compiler::Node*>{phi_bb5_7}, &block10, std::vector<compiler::Node*>{phi_bb5_7});
  }

  TNode<IntPtrT> phi_bb9_7;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_7);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), kConcatMethodName_0(state_));
  }

  TNode<IntPtrT> phi_bb10_7;
  TNode<Symbol> tmp11;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp12;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_7);
    tmp11 = CodeStubAssembler(state_).IteratorSymbolConstant();
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = GetMethod_3(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp8}, TNode<Symbol>{tmp11}, &label13);
    ca_.Goto(&block13, phi_bb10_7);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block14, phi_bb10_7);
    }
  }

  TNode<IntPtrT> phi_bb14_7;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_7);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kNotIterable), TNode<Object>{tmp8});
  }

  TNode<IntPtrT> phi_bb13_7;
  TNode<Union<HeapObject, TaggedIndex>> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<UintPtrT> tmp20;
  TNode<BoolT> tmp21;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7);
    std::tie(tmp14, tmp15, tmp16) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb3_6}).Flatten();
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp18 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp17}, TNode<IntPtrT>{phi_bb13_7});
    tmp19 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp18});
    tmp20 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp16});
    tmp21 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp19}, TNode<UintPtrT>{tmp20});
    ca_.Branch(tmp21, &block19, std::vector<compiler::Node*>{phi_bb13_7}, &block20, std::vector<compiler::Node*>{phi_bb13_7});
  }

  TNode<IntPtrT> phi_bb19_7;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Union<HeapObject, TaggedIndex>> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Union<HeapObject, TaggedIndex>> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_7);
    tmp22 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp18});
    tmp23 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp22});
    std::tie(tmp24, tmp25) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp14}, TNode<IntPtrT>{tmp23}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp24, tmp25}, tmp12);
    std::tie(tmp26, tmp27, tmp28) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb3_6}).Flatten();
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp30 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp29}, TNode<IntPtrT>{phi_bb19_7});
    tmp31 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp32 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp30}, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp28});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block27, std::vector<compiler::Node*>{phi_bb19_7}, &block28, std::vector<compiler::Node*>{phi_bb19_7});
  }

  TNode<IntPtrT> phi_bb20_7;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb27_7;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Union<HeapObject, TaggedIndex>> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_7);
    tmp36 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp32});
    tmp37 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp27}, TNode<IntPtrT>{tmp36});
    std::tie(tmp38, tmp39) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp26}, TNode<IntPtrT>{tmp37}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp38, tmp39}, tmp8);
    tmp40 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp41 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb27_7}, TNode<IntPtrT>{tmp40});
    ca_.Goto(&block7, tmp41);
  }

  TNode<IntPtrT> phi_bb28_7;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb6_7;
  TNode<JSIteratorConcatHelper> tmp42;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7);
    tmp42 = NewJSIteratorConcatHelper_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{phi_bb3_6});
    arguments.PopAndReturn(tmp42);
  }
}

TF_BUILTIN(IteratorConcatHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorConcatHelper> parameter1 = UncheckedParameter<JSIteratorConcatHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block37(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block38(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block39(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block41(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block52(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block53(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block58(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block59(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block60(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block61(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block62(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block63(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block64(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block65(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block70(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block71(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block72(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block76(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block77(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block78(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block79(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block80(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block81(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block82(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block83(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block84(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block85(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block86(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block87(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = IteratorHelperIsSuspendedStart_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp1 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp0});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    ca_.Goto(&block5, tmp1);
  }

  TNode<BoolT> phi_bb5_2;
  TNode<BoolT> tmp2;
      TNode<JSAny> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch3__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch3__label);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch3__label.is_used()) {
      compiler::CodeAssemblerLabel catch3_skip(&ca_);
      ca_.Goto(&catch3_skip);
      ca_.Bind(&catch3__label, &tmp4);
      ca_.Goto(&block6, phi_bb5_2);
      ca_.Bind(&catch3_skip);
    }
    ca_.Branch(tmp2, &block3, std::vector<compiler::Node*>{phi_bb5_2}, &block4, std::vector<compiler::Node*>{phi_bb5_2});
  }

  TNode<BoolT> phi_bb6_2;
  TNode<Union<JSMessageObject, TheHole>> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_2);
    tmp5 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb6_2, tmp4, tmp5);
  }

  TNode<BoolT> phi_bb3_2;
  TNode<BoolT> tmp6;
      TNode<JSAny> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch7__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch7__label);
    tmp6 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb3_2});
    }
    if (catch7__label.is_used()) {
      compiler::CodeAssemblerLabel catch7_skip(&ca_);
      ca_.Goto(&catch7_skip);
      ca_.Bind(&catch7__label, &tmp8);
      ca_.Goto(&block9, phi_bb3_2, phi_bb3_2);
      ca_.Bind(&catch7_skip);
    }
    ca_.Branch(tmp6, &block7, std::vector<compiler::Node*>{phi_bb3_2}, &block8, std::vector<compiler::Node*>{phi_bb3_2});
  }

  TNode<BoolT> phi_bb9_2;
  TNode<BoolT> phi_bb9_3;
  TNode<Union<JSMessageObject, TheHole>> tmp9;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_2, &phi_bb9_3);
    tmp9 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb9_2, tmp8, tmp9);
  }

  TNode<BoolT> phi_bb7_2;
  TNode<IntPtrT> tmp10;
      TNode<JSAny> tmp12;
  TNode<Smi> tmp13;
  TNode<IntPtrT> tmp14;
      TNode<JSAny> tmp16;
  TNode<IntPtrT> tmp17;
      TNode<JSAny> tmp19;
  TNode<FixedArray> tmp20;
  TNode<IntPtrT> tmp21;
      TNode<JSAny> tmp23;
  TNode<BoolT> tmp24;
      TNode<JSAny> tmp26;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch11__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch11__label);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch11__label.is_used()) {
      compiler::CodeAssemblerLabel catch11_skip(&ca_);
      ca_.Goto(&catch11_skip);
      ca_.Bind(&catch11__label, &tmp12);
      ca_.Goto(&block12, phi_bb7_2);
      ca_.Bind(&catch11_skip);
    }
    tmp13 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp10});
    compiler::CodeAssemblerExceptionHandlerLabel catch15__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch15__label);
    tmp14 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp13});
    }
    if (catch15__label.is_used()) {
      compiler::CodeAssemblerLabel catch15_skip(&ca_);
      ca_.Goto(&catch15_skip);
      ca_.Bind(&catch15__label, &tmp16);
      ca_.Goto(&block13, phi_bb7_2);
      ca_.Bind(&catch15_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch18__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch18__label);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch18__label.is_used()) {
      compiler::CodeAssemblerLabel catch18_skip(&ca_);
      ca_.Goto(&catch18_skip);
      ca_.Bind(&catch18__label, &tmp19);
      ca_.Goto(&block14, phi_bb7_2);
      ca_.Bind(&catch18_skip);
    }
    tmp20 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp17});
    compiler::CodeAssemblerExceptionHandlerLabel catch22__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch22__label);
    tmp21 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    }
    if (catch22__label.is_used()) {
      compiler::CodeAssemblerLabel catch22_skip(&ca_);
      ca_.Goto(&catch22_skip);
      ca_.Bind(&catch22__label, &tmp23);
      ca_.Goto(&block15, phi_bb7_2);
      ca_.Bind(&catch22_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch25__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch25__label);
    tmp24 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp21});
    }
    if (catch25__label.is_used()) {
      compiler::CodeAssemblerLabel catch25_skip(&ca_);
      ca_.Goto(&catch25_skip);
      ca_.Bind(&catch25__label, &tmp26);
      ca_.Goto(&block16, phi_bb7_2);
      ca_.Bind(&catch25_skip);
    }
    ca_.Branch(tmp24, &block10, std::vector<compiler::Node*>{phi_bb7_2}, &block11, std::vector<compiler::Node*>{phi_bb7_2});
  }

  TNode<BoolT> phi_bb12_2;
  TNode<Union<JSMessageObject, TheHole>> tmp27;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_2);
    tmp27 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb12_2, tmp12, tmp27);
  }

  TNode<BoolT> phi_bb13_2;
  TNode<Union<JSMessageObject, TheHole>> tmp28;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_2);
    tmp28 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb13_2, tmp16, tmp28);
  }

  TNode<BoolT> phi_bb14_2;
  TNode<Union<JSMessageObject, TheHole>> tmp29;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_2);
    tmp29 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb14_2, tmp19, tmp29);
  }

  TNode<BoolT> phi_bb15_2;
  TNode<Union<JSMessageObject, TheHole>> tmp30;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_2);
    tmp30 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb15_2, tmp23, tmp30);
  }

  TNode<BoolT> phi_bb16_2;
  TNode<Union<JSMessageObject, TheHole>> tmp31;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_2);
    tmp31 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb16_2, tmp26, tmp31);
  }

  TNode<BoolT> phi_bb10_2;
      TNode<JSAny> tmp33;
  TNode<Undefined> tmp34;
  TNode<True> tmp35;
  TNode<JSObject> tmp36;
      TNode<JSAny> tmp38;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch32__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch32__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch32__label.is_used()) {
      compiler::CodeAssemblerLabel catch32_skip(&ca_);
      ca_.Goto(&catch32_skip);
      ca_.Bind(&catch32__label, &tmp33);
      ca_.Goto(&block17, phi_bb10_2);
      ca_.Bind(&catch32_skip);
    }
    tmp34 = Undefined_0(state_);
    tmp35 = True_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch37__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch37__label);
    tmp36 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp34}, TNode<Boolean>{tmp35});
    }
    if (catch37__label.is_used()) {
      compiler::CodeAssemblerLabel catch37_skip(&ca_);
      ca_.Goto(&catch37_skip);
      ca_.Bind(&catch37__label, &tmp38);
      ca_.Goto(&block18, phi_bb10_2);
      ca_.Bind(&catch37_skip);
    }
    CodeStubAssembler(state_).Return(tmp36);
  }

  TNode<BoolT> phi_bb17_2;
  TNode<Union<JSMessageObject, TheHole>> tmp39;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_2);
    tmp39 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb17_2, tmp33, tmp39);
  }

  TNode<BoolT> phi_bb18_2;
  TNode<Union<JSMessageObject, TheHole>> tmp40;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_2);
    tmp40 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb18_2, tmp38, tmp40);
  }

  TNode<BoolT> phi_bb11_2;
  TNode<IntPtrT> tmp41;
      TNode<JSAny> tmp43;
  TNode<FixedArray> tmp44;
  TNode<Union<HeapObject, TaggedIndex>> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<IntPtrT> tmp47;
      TNode<JSAny> tmp49;
  TNode<IntPtrT> tmp50;
      TNode<JSAny> tmp52;
  TNode<Smi> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<UintPtrT> tmp55;
  TNode<UintPtrT> tmp56;
  TNode<BoolT> tmp57;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch42__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch42__label);
    tmp41 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch42__label.is_used()) {
      compiler::CodeAssemblerLabel catch42_skip(&ca_);
      ca_.Goto(&catch42_skip);
      ca_.Bind(&catch42__label, &tmp43);
      ca_.Goto(&block21, phi_bb11_2);
      ca_.Bind(&catch42_skip);
    }
    tmp44 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp41});
    compiler::CodeAssemblerExceptionHandlerLabel catch48__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch48__label);
    std::tie(tmp45, tmp46, tmp47) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp44}).Flatten();
    }
    if (catch48__label.is_used()) {
      compiler::CodeAssemblerLabel catch48_skip(&ca_);
      ca_.Goto(&catch48_skip);
      ca_.Bind(&catch48__label, &tmp49);
      ca_.Goto(&block22, phi_bb11_2);
      ca_.Bind(&catch48_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch51__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch51__label);
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch51__label.is_used()) {
      compiler::CodeAssemblerLabel catch51_skip(&ca_);
      ca_.Goto(&catch51_skip);
      ca_.Bind(&catch51__label, &tmp52);
      ca_.Goto(&block23, phi_bb11_2);
      ca_.Bind(&catch51_skip);
    }
    tmp53 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp50});
    tmp54 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp53});
    tmp55 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp54});
    tmp56 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp57 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp55}, TNode<UintPtrT>{tmp56});
    ca_.Branch(tmp57, &block28, std::vector<compiler::Node*>{phi_bb11_2}, &block29, std::vector<compiler::Node*>{phi_bb11_2});
  }

  TNode<BoolT> phi_bb21_2;
  TNode<Union<JSMessageObject, TheHole>> tmp58;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_2);
    tmp58 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb21_2, tmp43, tmp58);
  }

  TNode<BoolT> phi_bb22_2;
  TNode<Union<JSMessageObject, TheHole>> tmp59;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_2);
    tmp59 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb22_2, tmp49, tmp59);
  }

  TNode<BoolT> phi_bb23_2;
  TNode<Union<JSMessageObject, TheHole>> tmp60;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_2);
    tmp60 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb23_2, tmp52, tmp60);
  }

  TNode<BoolT> phi_bb28_2;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<Union<HeapObject, TaggedIndex>> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Object> tmp65;
  TNode<JSAny> tmp66;
      TNode<JSAny> tmp69;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_2);
    tmp61 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp54});
    tmp62 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp46}, TNode<IntPtrT>{tmp61});
    std::tie(tmp63, tmp64) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp45}, TNode<IntPtrT>{tmp62}).Flatten();
    tmp65 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp63, tmp64});
    compiler::CodeAssemblerLabel label67(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch68__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch68__label);
    tmp66 = Cast_JSAny_0(state_, TNode<Object>{tmp65}, &label67);
    }
    if (catch68__label.is_used()) {
      compiler::CodeAssemblerLabel catch68_skip(&ca_);
      ca_.Goto(&catch68_skip);
      ca_.Bind(&catch68__label, &tmp69);
      ca_.Goto(&block34, phi_bb28_2);
      ca_.Bind(&catch68_skip);
    }
    ca_.Goto(&block32, phi_bb28_2);
    if (label67.is_used()) {
      ca_.Bind(&label67);
      ca_.Goto(&block33, phi_bb28_2);
    }
  }

  TNode<BoolT> phi_bb29_2;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_2);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb34_2;
  TNode<Union<JSMessageObject, TheHole>> tmp70;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_2);
    tmp70 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb34_2, tmp69, tmp70);
  }

  TNode<BoolT> phi_bb33_2;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_2);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1315:23");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb32_2;
  TNode<IntPtrT> tmp71;
      TNode<JSAny> tmp73;
  TNode<FixedArray> tmp74;
  TNode<Union<HeapObject, TaggedIndex>> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
      TNode<JSAny> tmp79;
  TNode<IntPtrT> tmp80;
      TNode<JSAny> tmp82;
  TNode<Smi> tmp83;
  TNode<Smi> tmp84;
      TNode<JSAny> tmp86;
  TNode<Smi> tmp87;
      TNode<JSAny> tmp89;
  TNode<IntPtrT> tmp90;
  TNode<UintPtrT> tmp91;
  TNode<UintPtrT> tmp92;
  TNode<BoolT> tmp93;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch72__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch72__label);
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch72__label.is_used()) {
      compiler::CodeAssemblerLabel catch72_skip(&ca_);
      ca_.Goto(&catch72_skip);
      ca_.Bind(&catch72__label, &tmp73);
      ca_.Goto(&block37, phi_bb32_2);
      ca_.Bind(&catch72_skip);
    }
    tmp74 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp71});
    compiler::CodeAssemblerExceptionHandlerLabel catch78__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch78__label);
    std::tie(tmp75, tmp76, tmp77) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp74}).Flatten();
    }
    if (catch78__label.is_used()) {
      compiler::CodeAssemblerLabel catch78_skip(&ca_);
      ca_.Goto(&catch78_skip);
      ca_.Bind(&catch78__label, &tmp79);
      ca_.Goto(&block38, phi_bb32_2);
      ca_.Bind(&catch78_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch81__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch81__label);
    tmp80 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch81__label.is_used()) {
      compiler::CodeAssemblerLabel catch81_skip(&ca_);
      ca_.Goto(&catch81_skip);
      ca_.Bind(&catch81__label, &tmp82);
      ca_.Goto(&block39, phi_bb32_2);
      ca_.Bind(&catch81_skip);
    }
    tmp83 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp80});
    compiler::CodeAssemblerExceptionHandlerLabel catch85__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch85__label);
    tmp84 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch85__label.is_used()) {
      compiler::CodeAssemblerLabel catch85_skip(&ca_);
      ca_.Goto(&catch85_skip);
      ca_.Bind(&catch85__label, &tmp86);
      ca_.Goto(&block40, phi_bb32_2);
      ca_.Bind(&catch85_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch88__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch88__label);
    tmp87 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp83}, TNode<Smi>{tmp84});
    }
    if (catch88__label.is_used()) {
      compiler::CodeAssemblerLabel catch88_skip(&ca_);
      ca_.Goto(&catch88_skip);
      ca_.Bind(&catch88__label, &tmp89);
      ca_.Goto(&block41, phi_bb32_2);
      ca_.Bind(&catch88_skip);
    }
    tmp90 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp87});
    tmp91 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp90});
    tmp92 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp77});
    tmp93 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp91}, TNode<UintPtrT>{tmp92});
    ca_.Branch(tmp93, &block46, std::vector<compiler::Node*>{phi_bb32_2}, &block47, std::vector<compiler::Node*>{phi_bb32_2});
  }

  TNode<BoolT> phi_bb37_2;
  TNode<Union<JSMessageObject, TheHole>> tmp94;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_2);
    tmp94 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb37_2, tmp73, tmp94);
  }

  TNode<BoolT> phi_bb38_2;
  TNode<Union<JSMessageObject, TheHole>> tmp95;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_2);
    tmp95 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb38_2, tmp79, tmp95);
  }

  TNode<BoolT> phi_bb39_2;
  TNode<Union<JSMessageObject, TheHole>> tmp96;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_2);
    tmp96 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb39_2, tmp82, tmp96);
  }

  TNode<BoolT> phi_bb40_2;
  TNode<Union<JSMessageObject, TheHole>> tmp97;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_2);
    tmp97 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb40_2, tmp86, tmp97);
  }

  TNode<BoolT> phi_bb41_2;
  TNode<Union<JSMessageObject, TheHole>> tmp98;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_2);
    tmp98 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb41_2, tmp89, tmp98);
  }

  TNode<BoolT> phi_bb46_2;
  TNode<IntPtrT> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<Union<HeapObject, TaggedIndex>> tmp101;
  TNode<IntPtrT> tmp102;
  TNode<Object> tmp103;
  TNode<JSReceiver> tmp104;
      TNode<JSAny> tmp107;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_2);
    tmp99 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp90});
    tmp100 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp76}, TNode<IntPtrT>{tmp99});
    std::tie(tmp101, tmp102) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp75}, TNode<IntPtrT>{tmp100}).Flatten();
    tmp103 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp101, tmp102});
    compiler::CodeAssemblerLabel label105(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch106__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch106__label);
    tmp104 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp103}, &label105);
    }
    if (catch106__label.is_used()) {
      compiler::CodeAssemblerLabel catch106_skip(&ca_);
      ca_.Goto(&catch106_skip);
      ca_.Bind(&catch106__label, &tmp107);
      ca_.Goto(&block52, phi_bb46_2);
      ca_.Bind(&catch106_skip);
    }
    ca_.Goto(&block50, phi_bb46_2);
    if (label105.is_used()) {
      ca_.Bind(&label105);
      ca_.Goto(&block51, phi_bb46_2);
    }
  }

  TNode<BoolT> phi_bb47_2;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_2);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb52_2;
  TNode<Union<JSMessageObject, TheHole>> tmp108;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_2);
    tmp108 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb52_2, tmp107, tmp108);
  }

  TNode<BoolT> phi_bb51_2;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_2);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1318:23");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb50_2;
  TNode<JSAny> tmp109;
      TNode<JSAny> tmp111;
  TNode<JSReceiver> tmp112;
      TNode<JSAny> tmp115;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch110__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch110__label);
    tmp109 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp66}, TNode<JSAny>{tmp104});
    }
    if (catch110__label.is_used()) {
      compiler::CodeAssemblerLabel catch110_skip(&ca_);
      ca_.Goto(&catch110_skip);
      ca_.Bind(&catch110__label, &tmp111);
      ca_.Goto(&block53, phi_bb50_2);
      ca_.Bind(&catch110_skip);
    }
    compiler::CodeAssemblerLabel label113(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch114__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch114__label);
    tmp112 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp109}, &label113);
    }
    if (catch114__label.is_used()) {
      compiler::CodeAssemblerLabel catch114_skip(&ca_);
      ca_.Goto(&catch114_skip);
      ca_.Bind(&catch114__label, &tmp115);
      ca_.Goto(&block58, phi_bb50_2);
      ca_.Bind(&catch114_skip);
    }
    ca_.Goto(&block56, phi_bb50_2);
    if (label113.is_used()) {
      ca_.Bind(&label113);
      ca_.Goto(&block57, phi_bb50_2);
    }
  }

  TNode<BoolT> phi_bb53_2;
  TNode<Union<JSMessageObject, TheHole>> tmp116;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_2);
    tmp116 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb53_2, tmp111, tmp116);
  }

  TNode<BoolT> phi_bb58_2;
  TNode<Union<JSMessageObject, TheHole>> tmp117;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_2);
    tmp117 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb58_2, tmp115, tmp117);
  }

  TNode<BoolT> phi_bb57_2;
      TNode<JSAny> tmp119;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch118__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch118__label);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kNotIterable), TNode<Object>{tmp109});
    }
    if (catch118__label.is_used()) {
      compiler::CodeAssemblerLabel catch118_skip(&ca_);
      ca_.Bind(&catch118__label, &tmp119);
      ca_.Goto(&block59, phi_bb57_2);
    }
  }

  TNode<BoolT> phi_bb56_2;
  TNode<JSReceiver> tmp120;
  TNode<JSAny> tmp121;
      TNode<JSAny> tmp123;
  TNode<IntPtrT> tmp124;
      TNode<JSAny> tmp126;
  TNode<IntPtrT> tmp127;
      TNode<JSAny> tmp129;
  TNode<IntPtrT> tmp130;
      TNode<JSAny> tmp132;
  TNode<BoolT> tmp133;
      TNode<JSAny> tmp135;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch122__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch122__label);
    std::tie(tmp120, tmp121) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp112}).Flatten();
    }
    if (catch122__label.is_used()) {
      compiler::CodeAssemblerLabel catch122_skip(&ca_);
      ca_.Goto(&catch122_skip);
      ca_.Bind(&catch122__label, &tmp123);
      ca_.Goto(&block60, phi_bb56_2);
      ca_.Bind(&catch122_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch125__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch125__label);
    tmp124 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch125__label.is_used()) {
      compiler::CodeAssemblerLabel catch125_skip(&ca_);
      ca_.Goto(&catch125_skip);
      ca_.Bind(&catch125__label, &tmp126);
      ca_.Goto(&block61, phi_bb56_2);
      ca_.Bind(&catch125_skip);
    }
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp124}, tmp120);
    compiler::CodeAssemblerExceptionHandlerLabel catch128__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch128__label);
    tmp127 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch128__label.is_used()) {
      compiler::CodeAssemblerLabel catch128_skip(&ca_);
      ca_.Goto(&catch128_skip);
      ca_.Bind(&catch128__label, &tmp129);
      ca_.Goto(&block62, phi_bb56_2);
      ca_.Bind(&catch128_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch131__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch131__label);
    tmp130 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp124}, TNode<IntPtrT>{tmp127});
    }
    if (catch131__label.is_used()) {
      compiler::CodeAssemblerLabel catch131_skip(&ca_);
      ca_.Goto(&catch131_skip);
      ca_.Bind(&catch131__label, &tmp132);
      ca_.Goto(&block63, phi_bb56_2);
      ca_.Bind(&catch131_skip);
    }
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp130}, tmp121);
    compiler::CodeAssemblerExceptionHandlerLabel catch134__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch134__label);
    tmp133 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch134__label.is_used()) {
      compiler::CodeAssemblerLabel catch134_skip(&ca_);
      ca_.Goto(&catch134_skip);
      ca_.Bind(&catch134__label, &tmp135);
      ca_.Goto(&block64, phi_bb56_2);
      ca_.Bind(&catch134_skip);
    }
    ca_.Goto(&block8, tmp133);
  }

  TNode<BoolT> phi_bb59_2;
  TNode<Union<JSMessageObject, TheHole>> tmp136;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_2);
    tmp136 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb59_2, tmp119, tmp136);
  }

  TNode<BoolT> phi_bb60_2;
  TNode<Union<JSMessageObject, TheHole>> tmp137;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_2);
    tmp137 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb60_2, tmp123, tmp137);
  }

  TNode<BoolT> phi_bb61_2;
  TNode<Union<JSMessageObject, TheHole>> tmp138;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_2);
    tmp138 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb61_2, tmp126, tmp138);
  }

  TNode<BoolT> phi_bb62_2;
  TNode<Union<JSMessageObject, TheHole>> tmp139;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_2);
    tmp139 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb62_2, tmp129, tmp139);
  }

  TNode<BoolT> phi_bb63_2;
  TNode<Union<JSMessageObject, TheHole>> tmp140;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_2);
    tmp140 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb63_2, tmp132, tmp140);
  }

  TNode<BoolT> phi_bb64_2;
  TNode<Union<JSMessageObject, TheHole>> tmp141;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_2);
    tmp141 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb64_2, tmp135, tmp141);
  }

  TNode<BoolT> phi_bb8_2;
  TNode<Map> tmp142;
      TNode<JSAny> tmp144;
  TNode<IntPtrT> tmp145;
      TNode<JSAny> tmp147;
  TNode<JSReceiver> tmp148;
  TNode<IntPtrT> tmp149;
      TNode<JSAny> tmp151;
  TNode<IntPtrT> tmp152;
      TNode<JSAny> tmp154;
  TNode<JSAny> tmp155;
  TNode<JSAny> tmp156;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp159(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp160(&ca_);
      TNode<JSAny> tmp162;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch143__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch143__label);
    tmp142 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    }
    if (catch143__label.is_used()) {
      compiler::CodeAssemblerLabel catch143_skip(&ca_);
      ca_.Goto(&catch143_skip);
      ca_.Bind(&catch143__label, &tmp144);
      ca_.Goto(&block65, phi_bb8_2);
      ca_.Bind(&catch143_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch146__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch146__label);
    tmp145 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch146__label.is_used()) {
      compiler::CodeAssemblerLabel catch146_skip(&ca_);
      ca_.Goto(&catch146_skip);
      ca_.Bind(&catch146__label, &tmp147);
      ca_.Goto(&block70, phi_bb8_2);
      ca_.Bind(&catch146_skip);
    }
    tmp148 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp145});
    compiler::CodeAssemblerExceptionHandlerLabel catch150__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch150__label);
    tmp149 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    }
    if (catch150__label.is_used()) {
      compiler::CodeAssemblerLabel catch150_skip(&ca_);
      ca_.Goto(&catch150_skip);
      ca_.Bind(&catch150__label, &tmp151);
      ca_.Goto(&block71, phi_bb8_2);
      ca_.Bind(&catch150_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch153__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch153__label);
    tmp152 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp145}, TNode<IntPtrT>{tmp149});
    }
    if (catch153__label.is_used()) {
      compiler::CodeAssemblerLabel catch153_skip(&ca_);
      ca_.Goto(&catch153_skip);
      ca_.Bind(&catch153__label, &tmp154);
      ca_.Goto(&block72, phi_bb8_2);
      ca_.Bind(&catch153_skip);
    }
    tmp155 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{parameter1, tmp152});
    compiler::CodeAssemblerLabel label157(&ca_);
    compiler::CodeAssemblerLabel label158(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch161__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch161__label);
    tmp156 = IteratorStepValue_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp148}, TNode<JSAny>{tmp155}}, TNode<Map>{tmp142}, &label157, &label158, &tmp159, &tmp160);
    }
    if (catch161__label.is_used()) {
      compiler::CodeAssemblerLabel catch161_skip(&ca_);
      ca_.Goto(&catch161_skip);
      ca_.Bind(&catch161__label, &tmp162);
      ca_.Goto(&block76, phi_bb8_2);
      ca_.Bind(&catch161_skip);
    }
    ca_.Goto(&block73, phi_bb8_2);
    if (label157.is_used()) {
      ca_.Bind(&label157);
      ca_.Goto(&block74, phi_bb8_2);
    }
    if (label158.is_used()) {
      ca_.Bind(&label158);
      ca_.Goto(&block75, phi_bb8_2);
    }
  }

  TNode<BoolT> phi_bb65_2;
  TNode<Union<JSMessageObject, TheHole>> tmp163;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_2);
    tmp163 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb65_2, tmp144, tmp163);
  }

  TNode<BoolT> phi_bb70_2;
  TNode<Union<JSMessageObject, TheHole>> tmp164;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_2);
    tmp164 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb70_2, tmp147, tmp164);
  }

  TNode<BoolT> phi_bb71_2;
  TNode<Union<JSMessageObject, TheHole>> tmp165;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_2);
    tmp165 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb71_2, tmp151, tmp165);
  }

  TNode<BoolT> phi_bb72_2;
  TNode<Union<JSMessageObject, TheHole>> tmp166;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_2);
    tmp166 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb72_2, tmp154, tmp166);
  }

  TNode<BoolT> phi_bb76_2;
  TNode<Union<JSMessageObject, TheHole>> tmp167;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_2);
    tmp167 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb76_2, tmp162, tmp167);
  }

  TNode<BoolT> phi_bb74_2;
  TNode<BoolT> tmp168;
      TNode<JSAny> tmp170;
  TNode<IntPtrT> tmp171;
      TNode<JSAny> tmp173;
  TNode<IntPtrT> tmp174;
      TNode<JSAny> tmp176;
  TNode<Smi> tmp177;
  TNode<Smi> tmp178;
      TNode<JSAny> tmp180;
  TNode<Smi> tmp181;
      TNode<JSAny> tmp183;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch169__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch169__label);
    tmp168 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    }
    if (catch169__label.is_used()) {
      compiler::CodeAssemblerLabel catch169_skip(&ca_);
      ca_.Goto(&catch169_skip);
      ca_.Bind(&catch169__label, &tmp170);
      ca_.Goto(&block83, phi_bb74_2);
      ca_.Bind(&catch169_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch172__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch172__label);
    tmp171 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch172__label.is_used()) {
      compiler::CodeAssemblerLabel catch172_skip(&ca_);
      ca_.Goto(&catch172_skip);
      ca_.Bind(&catch172__label, &tmp173);
      ca_.Goto(&block84);
      ca_.Bind(&catch172_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch175__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch175__label);
    tmp174 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch175__label.is_used()) {
      compiler::CodeAssemblerLabel catch175_skip(&ca_);
      ca_.Goto(&catch175_skip);
      ca_.Bind(&catch175__label, &tmp176);
      ca_.Goto(&block85);
      ca_.Bind(&catch175_skip);
    }
    tmp177 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp174});
    compiler::CodeAssemblerExceptionHandlerLabel catch179__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch179__label);
    tmp178 = FromConstexpr_Smi_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch179__label.is_used()) {
      compiler::CodeAssemblerLabel catch179_skip(&ca_);
      ca_.Goto(&catch179_skip);
      ca_.Bind(&catch179__label, &tmp180);
      ca_.Goto(&block86);
      ca_.Bind(&catch179_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch182__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch182__label);
    tmp181 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp177}, TNode<Smi>{tmp178});
    }
    if (catch182__label.is_used()) {
      compiler::CodeAssemblerLabel catch182_skip(&ca_);
      ca_.Goto(&catch182_skip);
      ca_.Bind(&catch182__label, &tmp183);
      ca_.Goto(&block87);
      ca_.Bind(&catch182_skip);
    }
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp171}, tmp181);
    ca_.Goto(&block5, tmp168);
  }

  TNode<BoolT> phi_bb75_2;
  TNode<IntPtrT> tmp184;
      TNode<JSAny> tmp186;
  TNode<JSReceiver> tmp187;
      TNode<JSAny> tmp189;
      TNode<JSAny> tmp191;
      TNode<JSAny> tmp193;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch185__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch185__label);
    tmp184 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch185__label.is_used()) {
      compiler::CodeAssemblerLabel catch185_skip(&ca_);
      ca_.Goto(&catch185_skip);
      ca_.Bind(&catch185__label, &tmp186);
      ca_.Goto(&block79, phi_bb75_2);
      ca_.Bind(&catch185_skip);
    }
    tmp187 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp184});
    compiler::CodeAssemblerExceptionHandlerLabel catch188__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch188__label);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp187});
    }
    if (catch188__label.is_used()) {
      compiler::CodeAssemblerLabel catch188_skip(&ca_);
      ca_.Goto(&catch188_skip);
      ca_.Bind(&catch188__label, &tmp189);
      ca_.Goto(&block80, phi_bb75_2);
      ca_.Bind(&catch188_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch190__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch190__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch190__label.is_used()) {
      compiler::CodeAssemblerLabel catch190_skip(&ca_);
      ca_.Goto(&catch190_skip);
      ca_.Bind(&catch190__label, &tmp191);
      ca_.Goto(&block81, phi_bb75_2);
      ca_.Bind(&catch190_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch192__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch192__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp159.value(), tmp160.value());
    CodeStubAssembler(state_).Unreachable();
    }
    if (catch192__label.is_used()) {
      compiler::CodeAssemblerLabel catch192_skip(&ca_);
      ca_.Bind(&catch192__label, &tmp193);
      ca_.Goto(&block82, phi_bb75_2);
    }
  }

  TNode<BoolT> phi_bb73_2;
      TNode<JSAny> tmp195;
  TNode<False> tmp196;
  TNode<JSObject> tmp197;
      TNode<JSAny> tmp199;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_2);
    compiler::CodeAssemblerExceptionHandlerLabel catch194__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch194__label);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    }
    if (catch194__label.is_used()) {
      compiler::CodeAssemblerLabel catch194_skip(&ca_);
      ca_.Goto(&catch194_skip);
      ca_.Bind(&catch194__label, &tmp195);
      ca_.Goto(&block77, phi_bb73_2);
      ca_.Bind(&catch194_skip);
    }
    tmp196 = False_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch198__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch198__label);
    tmp197 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp156}, TNode<Boolean>{tmp196});
    }
    if (catch198__label.is_used()) {
      compiler::CodeAssemblerLabel catch198_skip(&ca_);
      ca_.Goto(&catch198_skip);
      ca_.Bind(&catch198__label, &tmp199);
      ca_.Goto(&block78, phi_bb73_2);
      ca_.Bind(&catch198_skip);
    }
    CodeStubAssembler(state_).Return(tmp197);
  }

  TNode<BoolT> phi_bb77_2;
  TNode<Union<JSMessageObject, TheHole>> tmp200;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_2);
    tmp200 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb77_2, tmp195, tmp200);
  }

  TNode<BoolT> phi_bb78_2;
  TNode<Union<JSMessageObject, TheHole>> tmp201;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_2);
    tmp201 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb78_2, tmp199, tmp201);
  }

  TNode<BoolT> phi_bb79_2;
  TNode<Union<JSMessageObject, TheHole>> tmp202;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_2);
    tmp202 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb79_2, tmp186, tmp202);
  }

  TNode<BoolT> phi_bb80_2;
  TNode<Union<JSMessageObject, TheHole>> tmp203;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_2);
    tmp203 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb80_2, tmp189, tmp203);
  }

  TNode<BoolT> phi_bb81_2;
  TNode<Union<JSMessageObject, TheHole>> tmp204;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_2);
    tmp204 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb81_2, tmp191, tmp204);
  }

  TNode<BoolT> phi_bb82_2;
  TNode<Union<JSMessageObject, TheHole>> tmp205;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_2);
    tmp205 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb82_2, tmp193, tmp205);
  }

  TNode<BoolT> phi_bb83_2;
  TNode<Union<JSMessageObject, TheHole>> tmp206;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_2);
    tmp206 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, phi_bb83_2, tmp170, tmp206);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp207;
  if (block84.is_used()) {
    ca_.Bind(&block84);
    tmp207 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp168, tmp173, tmp207);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp208;
  if (block85.is_used()) {
    ca_.Bind(&block85);
    tmp208 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp168, tmp176, tmp208);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp209;
  if (block86.is_used()) {
    ca_.Bind(&block86);
    tmp209 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp168, tmp180, tmp209);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp210;
  if (block87.is_used()) {
    ca_.Bind(&block87);
    tmp210 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block2, tmp168, tmp183, tmp210);
  }

  TNode<BoolT> phi_bb4_2;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_2);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1365:3");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb2_2;
  TNode<JSAny> phi_bb2_3;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_2, &phi_bb2_3, &phi_bb2_4);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{parameter1});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb2_3, phi_bb2_4);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(IteratorPrototypeJoin, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kSeparator);
  USE(parameter2);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kIteratorMethods));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, BoolT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.prototype.join");
  }

  TNode<Undefined> tmp2;
  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = Undefined_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{parameter2}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_String_constexpr_string_0(state_, ",");
    ca_.Goto(&block7, tmp4);
  }

  TNode<String> tmp5;
      TNode<JSAny> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    compiler::CodeAssemblerExceptionHandlerLabel catch6__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch6__label);
    tmp5 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter2});
    }
    if (catch6__label.is_used()) {
      compiler::CodeAssemblerLabel catch6_skip(&ca_);
      ca_.Goto(&catch6_skip);
      ca_.Bind(&catch6__label, &tmp7);
      ca_.Goto(&block10);
      ca_.Bind(&catch6_skip);
    }
    ca_.Goto(&block7, tmp5);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp8;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp8 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp7, tmp8);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb7_4;
  TNode<JSReceiver> tmp9;
  TNode<JSAny> tmp10;
  TNode<String> tmp11;
  TNode<BoolT> tmp12;
  TNode<Map> tmp13;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_4);
    std::tie(tmp9, tmp10) = GetIteratorDirect_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}).Flatten();
    tmp11 = kEmptyString_0(state_);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp13 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block13, tmp11, tmp12);
  }

  TNode<String> phi_bb13_7;
  TNode<BoolT> phi_bb13_8;
  TNode<BoolT> tmp14;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7, &phi_bb13_8);
    tmp14 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp14, &block11, std::vector<compiler::Node*>{phi_bb13_7, phi_bb13_8}, &block12, std::vector<compiler::Node*>{phi_bb13_7, phi_bb13_8});
  }

  TNode<String> phi_bb11_7;
  TNode<BoolT> phi_bb11_8;
  TNode<JSAny> tmp15;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp18(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp19(&ca_);
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7, &phi_bb11_8);
    compiler::CodeAssemblerLabel label16(&ca_);
    compiler::CodeAssemblerLabel label17(&ca_);
    tmp15 = IteratorStepValue_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp9}, TNode<JSAny>{tmp10}}, TNode<Map>{tmp13}, &label16, &label17, &tmp18, &tmp19);
    ca_.Goto(&block18, phi_bb11_7, phi_bb11_8);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block19, phi_bb11_7, phi_bb11_8);
    }
    if (label17.is_used()) {
      ca_.Bind(&label17);
      ca_.Goto(&block20, phi_bb11_7, phi_bb11_8);
    }
  }

  TNode<String> phi_bb19_7;
  TNode<BoolT> phi_bb19_8;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_7, &phi_bb19_8);
    CodeStubAssembler(state_).Return(phi_bb19_7);
  }

  TNode<String> phi_bb20_7;
  TNode<BoolT> phi_bb20_8;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7, &phi_bb20_8);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp18.value(), tmp19.value());
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb18_7;
  TNode<BoolT> phi_bb18_8;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_7, &phi_bb18_8);
    ca_.Branch(phi_bb18_8, &block21, std::vector<compiler::Node*>{phi_bb18_7, phi_bb18_8}, &block22, std::vector<compiler::Node*>{phi_bb18_7, phi_bb18_8});
  }

  TNode<String> phi_bb21_7;
  TNode<BoolT> phi_bb21_8;
  TNode<BoolT> tmp20;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7, &phi_bb21_8);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block23, phi_bb21_7, tmp20);
  }

  TNode<String> phi_bb22_7;
  TNode<BoolT> phi_bb22_8;
  TNode<String> tmp21;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7, &phi_bb22_8);
    tmp21 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{phi_bb22_7}, TNode<String>{phi_bb7_4});
    ca_.Goto(&block23, tmp21, phi_bb22_8);
  }

  TNode<String> phi_bb23_7;
  TNode<BoolT> phi_bb23_8;
  TNode<Undefined> tmp22;
  TNode<BoolT> tmp23;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_7, &phi_bb23_8);
    tmp22 = Undefined_0(state_);
    tmp23 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp15}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp22});
    ca_.Branch(tmp23, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  TNode<Null> tmp24;
  TNode<BoolT> tmp25;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp24 = Null_0(state_);
    tmp25 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp15}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp24});
    ca_.Goto(&block28, tmp25);
  }

  TNode<BoolT> tmp26;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp26 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block28, tmp26);
  }

  TNode<BoolT> phi_bb28_12;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_12);
    ca_.Branch(phi_bb28_12, &block24, std::vector<compiler::Node*>{}, &block25, std::vector<compiler::Node*>{phi_bb23_7});
  }

  TNode<String> tmp27;
      TNode<JSAny> tmp29;
  TNode<String> tmp30;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    compiler::CodeAssemblerExceptionHandlerLabel catch28__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch28__label);
    tmp27 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp15});
    }
    if (catch28__label.is_used()) {
      compiler::CodeAssemblerLabel catch28_skip(&ca_);
      ca_.Goto(&catch28_skip);
      ca_.Bind(&catch28__label, &tmp29);
      ca_.Goto(&block31);
      ca_.Bind(&catch28_skip);
    }
    tmp30 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{phi_bb23_7}, TNode<String>{tmp27});
    ca_.Goto(&block25, tmp30);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp31;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp31 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp29, tmp31);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb25_7;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_7);
    ca_.Goto(&block13, phi_bb25_7, phi_bb23_8);
  }

  TNode<String> phi_bb12_7;
  TNode<BoolT> phi_bb12_8;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_7, &phi_bb12_8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1454:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1459&c=1
void IteratorZipCloseAll_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterators, bool p_propagate) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block37(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT, IntPtrT> block38(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{p_iterators, tmp0});
    tmp2 = FromConstexpr_uint32_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp3 = CodeStubAssembler(state_).Uint32Mod(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp2});
    tmp4 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp3}, TNode<Uint32T>{tmp4});
    ca_.Branch(tmp5, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1462});
      CodeStubAssembler(state_).FailAssert("Torque assert 'iterators.length % kIteratorRecordFieldCount == 0' failed", pos_stack);
    }
  }

  TNode<Undefined> tmp6;
  TNode<TheHole> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp6 = Undefined_0(state_);
    tmp7 = TheHole_0(state_);
    tmp8 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{p_iterators});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp10 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp9});
    ca_.Goto(&block6, tmp6, tmp7, tmp10);
  }

  TNode<JSAny> phi_bb6_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb6_3;
  TNode<IntPtrT> phi_bb6_4;
  TNode<IntPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_2, &phi_bb6_3, &phi_bb6_4);
    tmp11 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp12 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb6_4}, TNode<IntPtrT>{tmp11});
    ca_.Branch(tmp12, &block4, std::vector<compiler::Node*>{phi_bb6_2, phi_bb6_3, phi_bb6_4}, &block5, std::vector<compiler::Node*>{phi_bb6_2, phi_bb6_3, phi_bb6_4});
  }

  TNode<JSAny> phi_bb4_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb4_3;
  TNode<IntPtrT> phi_bb4_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_2, &phi_bb4_3, &phi_bb4_4);
    std::tie(tmp13, tmp14, tmp15) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_iterators}).Flatten();
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb4_4});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block12, std::vector<compiler::Node*>{phi_bb4_2, phi_bb4_3, phi_bb4_4, phi_bb4_4, phi_bb4_4, phi_bb4_4, phi_bb4_4}, &block13, std::vector<compiler::Node*>{phi_bb4_2, phi_bb4_3, phi_bb4_4, phi_bb4_4, phi_bb4_4, phi_bb4_4, phi_bb4_4});
  }

  TNode<JSAny> phi_bb12_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb12_3;
  TNode<IntPtrT> phi_bb12_4;
  TNode<IntPtrT> phi_bb12_9;
  TNode<IntPtrT> phi_bb12_10;
  TNode<IntPtrT> phi_bb12_14;
  TNode<IntPtrT> phi_bb12_15;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<Object> tmp23;
  TNode<TheHole> tmp24;
  TNode<BoolT> tmp25;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_2, &phi_bb12_3, &phi_bb12_4, &phi_bb12_9, &phi_bb12_10, &phi_bb12_14, &phi_bb12_15);
    tmp19 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb12_15});
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp19});
    std::tie(tmp21, tmp22) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp13}, TNode<IntPtrT>{tmp20}).Flatten();
    tmp23 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp21, tmp22});
    tmp24 = TheHole_0(state_);
    tmp25 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp23}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp24});
    ca_.Branch(tmp25, &block16, std::vector<compiler::Node*>{phi_bb12_2, phi_bb12_3, phi_bb12_4}, &block17, std::vector<compiler::Node*>{phi_bb12_2, phi_bb12_3, phi_bb12_4});
  }

  TNode<JSAny> phi_bb13_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb13_3;
  TNode<IntPtrT> phi_bb13_4;
  TNode<IntPtrT> phi_bb13_9;
  TNode<IntPtrT> phi_bb13_10;
  TNode<IntPtrT> phi_bb13_14;
  TNode<IntPtrT> phi_bb13_15;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_2, &phi_bb13_3, &phi_bb13_4, &phi_bb13_9, &phi_bb13_10, &phi_bb13_14, &phi_bb13_15);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb16_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb16_3;
  TNode<IntPtrT> phi_bb16_4;
  TNode<JSReceiver> tmp26;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_2, &phi_bb16_3, &phi_bb16_4);
    compiler::CodeAssemblerLabel label27(&ca_);
    tmp26 = Cast_JSReceiver_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp23}, &label27);
    ca_.Goto(&block20, phi_bb16_2, phi_bb16_3, phi_bb16_4);
    if (label27.is_used()) {
      ca_.Bind(&label27);
      ca_.Goto(&block21, phi_bb16_2, phi_bb16_3, phi_bb16_4);
    }
  }

  TNode<JSAny> phi_bb21_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb21_3;
  TNode<IntPtrT> phi_bb21_4;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_2, &phi_bb21_3, &phi_bb21_4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1469:55");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb20_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb20_3;
  TNode<IntPtrT> phi_bb20_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<UintPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<BoolT> tmp33;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_2, &phi_bb20_3, &phi_bb20_4);
    std::tie(tmp28, tmp29, tmp30) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_iterators}).Flatten();
    tmp31 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb20_4});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp33 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp31}, TNode<UintPtrT>{tmp32});
    ca_.Branch(tmp33, &block26, std::vector<compiler::Node*>{phi_bb20_2, phi_bb20_3, phi_bb20_4, phi_bb20_4, phi_bb20_4, phi_bb20_4, phi_bb20_4}, &block27, std::vector<compiler::Node*>{phi_bb20_2, phi_bb20_3, phi_bb20_4, phi_bb20_4, phi_bb20_4, phi_bb20_4, phi_bb20_4});
  }

  TNode<JSAny> phi_bb26_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb26_3;
  TNode<IntPtrT> phi_bb26_4;
  TNode<IntPtrT> phi_bb26_11;
  TNode<IntPtrT> phi_bb26_12;
  TNode<IntPtrT> phi_bb26_16;
  TNode<IntPtrT> phi_bb26_17;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<Union<HeapObject, TaggedIndex>> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<TheHole> tmp38;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_2, &phi_bb26_3, &phi_bb26_4, &phi_bb26_11, &phi_bb26_12, &phi_bb26_16, &phi_bb26_17);
    tmp34 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb26_17});
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp29}, TNode<IntPtrT>{tmp34});
    std::tie(tmp36, tmp37) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp28}, TNode<IntPtrT>{tmp35}).Flatten();
    tmp38 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp36, tmp37}, tmp38);
    if ((p_propagate)) {
      ca_.Goto(&block30, phi_bb26_2, phi_bb26_3, phi_bb26_4);
    } else {
      ca_.Goto(&block31, phi_bb26_2, phi_bb26_3, phi_bb26_4);
    }
  }

  TNode<JSAny> phi_bb27_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb27_3;
  TNode<IntPtrT> phi_bb27_4;
  TNode<IntPtrT> phi_bb27_11;
  TNode<IntPtrT> phi_bb27_12;
  TNode<IntPtrT> phi_bb27_16;
  TNode<IntPtrT> phi_bb27_17;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_2, &phi_bb27_3, &phi_bb27_4, &phi_bb27_11, &phi_bb27_12, &phi_bb27_16, &phi_bb27_17);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb30_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb30_3;
  TNode<IntPtrT> phi_bb30_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
      TNode<JSAny> tmp43;
  TNode<IntPtrT> tmp44;
      TNode<JSAny> tmp46;
  TNode<IntPtrT> tmp47;
      TNode<JSAny> tmp49;
  TNode<UintPtrT> tmp50;
  TNode<UintPtrT> tmp51;
  TNode<BoolT> tmp52;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_2, &phi_bb30_3, &phi_bb30_4);
    compiler::CodeAssemblerExceptionHandlerLabel catch42__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch42__label);
    std::tie(tmp39, tmp40, tmp41) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_iterators}).Flatten();
    }
    if (catch42__label.is_used()) {
      compiler::CodeAssemblerLabel catch42_skip(&ca_);
      ca_.Goto(&catch42_skip);
      ca_.Bind(&catch42__label, &tmp43);
      ca_.Goto(&block37, phi_bb30_2, phi_bb30_3, phi_bb30_4);
      ca_.Bind(&catch42_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch45__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch45__label);
    tmp44 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch45__label.is_used()) {
      compiler::CodeAssemblerLabel catch45_skip(&ca_);
      ca_.Goto(&catch45_skip);
      ca_.Bind(&catch45__label, &tmp46);
      ca_.Goto(&block38, phi_bb30_2, phi_bb30_3, phi_bb30_4, phi_bb30_4, phi_bb30_4);
      ca_.Bind(&catch45_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch48__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch48__label);
    tmp47 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb30_4}, TNode<IntPtrT>{tmp44});
    }
    if (catch48__label.is_used()) {
      compiler::CodeAssemblerLabel catch48_skip(&ca_);
      ca_.Goto(&catch48_skip);
      ca_.Bind(&catch48__label, &tmp49);
      ca_.Goto(&block39, phi_bb30_2, phi_bb30_3, phi_bb30_4, phi_bb30_4);
      ca_.Bind(&catch48_skip);
    }
    tmp50 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp51 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp41});
    tmp52 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp50}, TNode<UintPtrT>{tmp51});
    ca_.Branch(tmp52, &block44, std::vector<compiler::Node*>{phi_bb30_2, phi_bb30_3, phi_bb30_4}, &block45, std::vector<compiler::Node*>{phi_bb30_2, phi_bb30_3, phi_bb30_4});
  }

  TNode<JSAny> phi_bb37_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb37_3;
  TNode<IntPtrT> phi_bb37_4;
  TNode<Union<JSMessageObject, TheHole>> tmp53;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_2, &phi_bb37_3, &phi_bb37_4);
    tmp53 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block34, phi_bb37_2, phi_bb37_3, phi_bb37_4, tmp43, tmp53);
  }

  TNode<JSAny> phi_bb38_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb38_3;
  TNode<IntPtrT> phi_bb38_4;
  TNode<IntPtrT> phi_bb38_11;
  TNode<IntPtrT> phi_bb38_12;
  TNode<Union<JSMessageObject, TheHole>> tmp54;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_2, &phi_bb38_3, &phi_bb38_4, &phi_bb38_11, &phi_bb38_12);
    tmp54 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block34, phi_bb38_2, phi_bb38_3, phi_bb38_4, tmp46, tmp54);
  }

  TNode<JSAny> phi_bb39_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb39_3;
  TNode<IntPtrT> phi_bb39_4;
  TNode<IntPtrT> phi_bb39_11;
  TNode<Union<JSMessageObject, TheHole>> tmp55;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_2, &phi_bb39_3, &phi_bb39_4, &phi_bb39_11);
    tmp55 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block34, phi_bb39_2, phi_bb39_3, phi_bb39_4, tmp49, tmp55);
  }

  TNode<JSAny> phi_bb44_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb44_3;
  TNode<IntPtrT> phi_bb44_4;
  TNode<IntPtrT> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<Union<HeapObject, TaggedIndex>> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<Object> tmp60;
  TNode<JSAny> tmp61;
      TNode<JSAny> tmp64;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_2, &phi_bb44_3, &phi_bb44_4);
    tmp56 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp47});
    tmp57 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp40}, TNode<IntPtrT>{tmp56});
    std::tie(tmp58, tmp59) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp39}, TNode<IntPtrT>{tmp57}).Flatten();
    tmp60 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp58, tmp59});
    compiler::CodeAssemblerLabel label62(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch63__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch63__label);
    tmp61 = Cast_JSAny_0(state_, TNode<Object>{tmp60}, &label62);
    }
    if (catch63__label.is_used()) {
      compiler::CodeAssemblerLabel catch63_skip(&ca_);
      ca_.Goto(&catch63_skip);
      ca_.Bind(&catch63__label, &tmp64);
      ca_.Goto(&block50, phi_bb44_2, phi_bb44_3, phi_bb44_4);
      ca_.Bind(&catch63_skip);
    }
    ca_.Goto(&block48, phi_bb44_2, phi_bb44_3, phi_bb44_4);
    if (label62.is_used()) {
      ca_.Bind(&label62);
      ca_.Goto(&block49, phi_bb44_2, phi_bb44_3, phi_bb44_4);
    }
  }

  TNode<JSAny> phi_bb45_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb45_3;
  TNode<IntPtrT> phi_bb45_4;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_2, &phi_bb45_3, &phi_bb45_4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb50_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb50_3;
  TNode<IntPtrT> phi_bb50_4;
  TNode<Union<JSMessageObject, TheHole>> tmp65;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_2, &phi_bb50_3, &phi_bb50_4);
    tmp65 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block34, phi_bb50_2, phi_bb50_3, phi_bb50_4, tmp64, tmp65);
  }

  TNode<JSAny> phi_bb49_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb49_3;
  TNode<IntPtrT> phi_bb49_4;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_2, &phi_bb49_3, &phi_bb49_4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1474:25");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb48_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb48_3;
  TNode<IntPtrT> phi_bb48_4;
      TNode<JSAny> tmp67;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_2, &phi_bb48_3, &phi_bb48_4);
    compiler::CodeAssemblerExceptionHandlerLabel catch66__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch66__label);
    IteratorClose_0(state_, TNode<Context>{p_context}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp26}, TNode<JSAny>{tmp61}});
    }
    if (catch66__label.is_used()) {
      compiler::CodeAssemblerLabel catch66_skip(&ca_);
      ca_.Goto(&catch66_skip);
      ca_.Bind(&catch66__label, &tmp67);
      ca_.Goto(&block51, phi_bb48_2, phi_bb48_3, phi_bb48_4);
      ca_.Bind(&catch66_skip);
    }
    ca_.Goto(&block33, phi_bb48_2, phi_bb48_3, phi_bb48_4);
  }

  TNode<JSAny> phi_bb51_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb51_3;
  TNode<IntPtrT> phi_bb51_4;
  TNode<Union<JSMessageObject, TheHole>> tmp68;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_2, &phi_bb51_3, &phi_bb51_4);
    tmp68 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block34, phi_bb51_2, phi_bb51_3, phi_bb51_4, tmp67, tmp68);
  }

  TNode<JSAny> phi_bb34_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb34_3;
  TNode<IntPtrT> phi_bb34_4;
  TNode<JSAny> phi_bb34_7;
  TNode<Union<JSMessageObject, TheHole>> phi_bb34_8;
  TNode<Undefined> tmp69;
  TNode<BoolT> tmp70;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_2, &phi_bb34_3, &phi_bb34_4, &phi_bb34_7, &phi_bb34_8);
    tmp69 = Undefined_0(state_);
    tmp70 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{phi_bb34_2}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp69});
    ca_.Branch(tmp70, &block52, std::vector<compiler::Node*>{phi_bb34_2, phi_bb34_3, phi_bb34_4}, &block53, std::vector<compiler::Node*>{phi_bb34_2, phi_bb34_3, phi_bb34_4});
  }

  TNode<JSAny> phi_bb52_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb52_3;
  TNode<IntPtrT> phi_bb52_4;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_2, &phi_bb52_3, &phi_bb52_4);
    ca_.Goto(&block53, phi_bb34_7, phi_bb34_8, phi_bb52_4);
  }

  TNode<JSAny> phi_bb53_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb53_3;
  TNode<IntPtrT> phi_bb53_4;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_2, &phi_bb53_3, &phi_bb53_4);
    ca_.Goto(&block33, phi_bb53_2, phi_bb53_3, phi_bb53_4);
  }

  TNode<JSAny> phi_bb33_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb33_3;
  TNode<IntPtrT> phi_bb33_4;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_2, &phi_bb33_3, &phi_bb33_4);
    ca_.Goto(&block32, phi_bb33_2, phi_bb33_3, phi_bb33_4);
  }

  TNode<JSAny> phi_bb31_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb31_3;
  TNode<IntPtrT> phi_bb31_4;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_2, &phi_bb31_3, &phi_bb31_4);
    IteratorCloseOnException_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{tmp26});
    ca_.Goto(&block32, phi_bb31_2, phi_bb31_3, phi_bb31_4);
  }

  TNode<JSAny> phi_bb32_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb32_3;
  TNode<IntPtrT> phi_bb32_4;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_2, &phi_bb32_3, &phi_bb32_4);
    ca_.Goto(&block17, phi_bb32_2, phi_bb32_3, phi_bb32_4);
  }

  TNode<JSAny> phi_bb17_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb17_3;
  TNode<IntPtrT> phi_bb17_4;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_2, &phi_bb17_3, &phi_bb17_4);
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp72 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb17_4}, TNode<IntPtrT>{tmp71});
    ca_.Goto(&block6, phi_bb17_2, phi_bb17_3, tmp72);
  }

  TNode<JSAny> phi_bb5_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb5_3;
  TNode<IntPtrT> phi_bb5_4;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_2, &phi_bb5_3, &phi_bb5_4);
    if ((p_propagate)) {
      ca_.Goto(&block54, phi_bb5_2, phi_bb5_3);
    } else {
      ca_.Goto(&block55, phi_bb5_2, phi_bb5_3);
    }
  }

  TNode<JSAny> phi_bb54_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb54_3;
  TNode<Undefined> tmp73;
  TNode<BoolT> tmp74;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_2, &phi_bb54_3);
    tmp73 = Undefined_0(state_);
    tmp74 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{phi_bb54_2}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp73});
    ca_.Branch(tmp74, &block57, std::vector<compiler::Node*>{phi_bb54_2, phi_bb54_3}, &block58, std::vector<compiler::Node*>{phi_bb54_2, phi_bb54_3});
  }

  TNode<JSAny> phi_bb57_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb57_3;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_2, &phi_bb57_3);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, p_context, phi_bb57_2, phi_bb57_3);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb58_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb58_3;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_2, &phi_bb58_3);
    ca_.Goto(&block56, phi_bb58_2, phi_bb58_3);
  }

  TNode<JSAny> phi_bb55_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb55_3;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_2, &phi_bb55_3);
    ca_.Goto(&block56, phi_bb55_2, phi_bb55_3);
  }

  TNode<JSAny> phi_bb56_2;
  TNode<Union<JSMessageObject, TheHole>> phi_bb56_3;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_2, &phi_bb56_3);
    ca_.Goto(&block59);
  }

    ca_.Bind(&block59);
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1494&c=1
TNode<JSIteratorZipHelper> NewJSIteratorZipHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterators, TNode<FixedArray> p_padding, TNode<Uint32T> p_zipMode) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{p_iterators, tmp0});
    tmp2 = FromConstexpr_uint32_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp3 = CodeStubAssembler(state_).Uint32Mod(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp2});
    tmp4 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp3}, TNode<Uint32T>{tmp4});
    ca_.Branch(tmp5, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1497});
      CodeStubAssembler(state_).FailAssert("Torque assert 'iterators.length % kIteratorRecordFieldCount == 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<Union<HeapObject, TaggedIndex>> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<FixedArray> tmp10;
  TNode<FixedArray> tmp11;
  TNode<Uint32T> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Smi> tmp18;
  TNode<BoolT> tmp19;
  TNode<BoolT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<HeapObject> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<JSIteratorZipHelper> tmp31;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp6 = ITERATOR_ZIP_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp7, tmp8) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp6}).Flatten();
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp7, tmp8});
    tmp10 = kEmptyFixedArray_0(state_);
    tmp11 = kEmptyFixedArray_0(state_);
    tmp12 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp13 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp12});
    tmp14 = SmiTag_JSIteratorZipHelperMode_0(state_, TNode<Uint32T>{p_zipMode});
    tmp15 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{p_iterators});
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp17 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp16});
    tmp18 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{tmp17});
    tmp19 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp22 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp21}, TNode<Map>{tmp9}, TNode<BoolT>{tmp19}, TNode<BoolT>{tmp20});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp22, tmp23}, tmp9);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp22, tmp24}, tmp10);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp22, tmp25}, tmp11);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp26}, tmp13);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp22, tmp27}, p_iterators);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp28}, tmp14);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp29}, tmp18);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp22, tmp30}, p_padding);
    tmp31 = TORQUE_CAST(TNode<HeapObject>{tmp22});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSIteratorZipHelper>{tmp31};
}

TF_BUILTIN(IteratorZip, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, BoolT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block41(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block43(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block46(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block48(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block54(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block61(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block63(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block75(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray> block80(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray> block82(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray> block84(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block95(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block97(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block96(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block99(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block98(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block100(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, JSAny> block106(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block109(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block111(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block113(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT> block118(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block133(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block137(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block139(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block141(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT> block140(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT> block146(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT> block149(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT> block148(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT> block151(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT> block153(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, BoolT> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block156(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block158(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block157(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block160(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<BoolT> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    tmp2 = Is_JSReceiver_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp1});
    tmp3 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp2});
    ca_.Branch(tmp3, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.zip");
  }

  TNode<IntPtrT> tmp4;
  TNode<JSAny> tmp5;
  TNode<JSReceiver> tmp6;
  TNode<Uint32T> tmp7;
  TNode<JSAny> tmp8;
  TNode<JSAny> tmp9;
  TNode<Undefined> tmp10;
  TNode<BoolT> tmp11;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp5 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp4});
    tmp6 = GetOptionsObject_0(state_, TNode<NativeContext>{parameter0}, TNode<JSAny>{tmp5});
    tmp7 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kShortest_0(state_, JSIteratorZipHelperMode::kShortest);
    tmp8 = FromConstexpr_JSAny_constexpr_string_0(state_, "mode");
    tmp9 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp6}, TNode<JSAny>{tmp8});
    tmp10 = Undefined_0(state_);
    tmp11 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp9}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp10});
    ca_.Branch(tmp11, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{tmp7});
  }

  TNode<String> tmp12;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = Cast_String_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp9}, &label13);
    ca_.Goto(&block7);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidIteratorZipMode), "Iterator.zip");
  }

  TNode<String> tmp14;
  TNode<Oddball> tmp15;
  TNode<True> tmp16;
  TNode<BoolT> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp14 = CodeStubAssembler(state_).StringConstant("shortest");
    tmp15 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kStringEqual, parameter0, tmp12, tmp14)); 
    tmp16 = True_0(state_);
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp15}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp16});
    ca_.Branch(tmp17, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp18;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp18 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kShortest_0(state_, JSIteratorZipHelperMode::kShortest);
    ca_.Goto(&block11, tmp18);
  }

  TNode<String> tmp19;
  TNode<Oddball> tmp20;
  TNode<True> tmp21;
  TNode<BoolT> tmp22;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp19 = CodeStubAssembler(state_).StringConstant("longest");
    tmp20 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kStringEqual, parameter0, tmp12, tmp19)); 
    tmp21 = True_0(state_);
    tmp22 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp20}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp21});
    ca_.Branch(tmp22, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp23;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp23 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kLongest_0(state_, JSIteratorZipHelperMode::kLongest);
    ca_.Goto(&block14, tmp23);
  }

  TNode<String> tmp24;
  TNode<Oddball> tmp25;
  TNode<True> tmp26;
  TNode<BoolT> tmp27;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp24 = CodeStubAssembler(state_).StringConstant("strict");
    tmp25 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kStringEqual, parameter0, tmp12, tmp24)); 
    tmp26 = True_0(state_);
    tmp27 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp25}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp26});
    ca_.Branch(tmp27, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp28;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp28 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kStrict_0(state_, JSIteratorZipHelperMode::kStrict);
    ca_.Goto(&block14, tmp28);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidIteratorZipMode), "Iterator.zip");
  }

  TNode<Uint32T> phi_bb14_8;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_8);
    ca_.Goto(&block11, phi_bb14_8);
  }

  TNode<Uint32T> phi_bb11_8;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_8);
    ca_.Goto(&block4, phi_bb11_8);
  }

  TNode<Uint32T> phi_bb4_8;
  TNode<Undefined> tmp29;
  TNode<Uint32T> tmp30;
  TNode<BoolT> tmp31;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_8);
    tmp29 = Undefined_0(state_);
    tmp30 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kLongest));
    tmp31 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{phi_bb4_8}, TNode<Uint32T>{tmp30});
    ca_.Branch(tmp31, &block18, std::vector<compiler::Node*>{phi_bb4_8}, &block19, std::vector<compiler::Node*>{phi_bb4_8, tmp29});
  }

  TNode<Uint32T> phi_bb18_8;
  TNode<JSAny> tmp32;
  TNode<JSAny> tmp33;
  TNode<Undefined> tmp34;
  TNode<BoolT> tmp35;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_8);
    tmp32 = FromConstexpr_JSAny_constexpr_string_0(state_, "padding");
    tmp33 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp6}, TNode<JSAny>{tmp32});
    tmp34 = Undefined_0(state_);
    tmp35 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp33}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp34});
    ca_.Branch(tmp35, &block22, std::vector<compiler::Node*>{phi_bb18_8}, &block23, std::vector<compiler::Node*>{phi_bb18_8});
  }

  TNode<Uint32T> phi_bb22_8;
  TNode<BoolT> tmp36;
  TNode<BoolT> tmp37;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_8);
    tmp36 = Is_JSReceiver_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp33});
    tmp37 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp36});
    ca_.Goto(&block24, phi_bb22_8, tmp37);
  }

  TNode<Uint32T> phi_bb23_8;
  TNode<BoolT> tmp38;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_8);
    tmp38 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block24, phi_bb23_8, tmp38);
  }

  TNode<Uint32T> phi_bb24_8;
  TNode<BoolT> phi_bb24_12;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_8, &phi_bb24_12);
    ca_.Branch(phi_bb24_12, &block20, std::vector<compiler::Node*>{phi_bb24_8}, &block21, std::vector<compiler::Node*>{phi_bb24_8});
  }

  TNode<Uint32T> phi_bb20_8;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_8);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "padding");
  }

  TNode<Uint32T> phi_bb21_8;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_8);
    ca_.Goto(&block19, phi_bb21_8, tmp33);
  }

  TNode<Uint32T> phi_bb19_8;
  TNode<JSAny> phi_bb19_10;
  TNode<FixedArray> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<FixedArray> tmp42;
  TNode<Map> tmp43;
  TNode<JSReceiver> tmp44;
  TNode<JSAny> tmp45;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_8, &phi_bb19_10);
    std::tie(tmp39, tmp40, tmp41) = NewGrowableFixedArray_0(state_).Flatten();
    tmp42 = kEmptyFixedArray_0(state_);
    tmp43 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    std::tie(tmp44, tmp45) = IteratorBuiltinsAssembler(state_).GetIterator(TNode<Context>{parameter0}, TNode<JSAny>{tmp1}).Flatten();
    ca_.Goto(&block31, phi_bb19_8, phi_bb19_10, tmp39, tmp40, tmp41);
  }

  TNode<Uint32T> phi_bb31_8;
  TNode<JSAny> phi_bb31_10;
  TNode<FixedArray> phi_bb31_11;
  TNode<IntPtrT> phi_bb31_12;
  TNode<IntPtrT> phi_bb31_13;
  TNode<BoolT> tmp46;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_8, &phi_bb31_10, &phi_bb31_11, &phi_bb31_12, &phi_bb31_13);
    tmp46 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp46, &block29, std::vector<compiler::Node*>{phi_bb31_8, phi_bb31_10, phi_bb31_11, phi_bb31_12, phi_bb31_13}, &block30, std::vector<compiler::Node*>{phi_bb31_8, phi_bb31_10, phi_bb31_11, phi_bb31_12, phi_bb31_13});
  }

  TNode<Uint32T> phi_bb29_8;
  TNode<JSAny> phi_bb29_10;
  TNode<FixedArray> phi_bb29_11;
  TNode<IntPtrT> phi_bb29_12;
  TNode<IntPtrT> phi_bb29_13;
  TNode<JSAny> tmp47;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp50(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp51(&ca_);
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_8, &phi_bb29_10, &phi_bb29_11, &phi_bb29_12, &phi_bb29_13);
    compiler::CodeAssemblerLabel label48(&ca_);
    compiler::CodeAssemblerLabel label49(&ca_);
    tmp47 = IteratorStepValue_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp44}, TNode<JSAny>{tmp45}}, TNode<Map>{tmp43}, &label48, &label49, &tmp50, &tmp51);
    ca_.Goto(&block32, phi_bb29_8, phi_bb29_10, phi_bb29_11, phi_bb29_12, phi_bb29_13);
    if (label48.is_used()) {
      ca_.Bind(&label48);
      ca_.Goto(&block33, phi_bb29_8, phi_bb29_10, phi_bb29_11, phi_bb29_12, phi_bb29_13);
    }
    if (label49.is_used()) {
      ca_.Bind(&label49);
      ca_.Goto(&block34, phi_bb29_8, phi_bb29_10, phi_bb29_11, phi_bb29_12, phi_bb29_13);
    }
  }

  TNode<Uint32T> phi_bb33_8;
  TNode<JSAny> phi_bb33_10;
  TNode<FixedArray> phi_bb33_11;
  TNode<IntPtrT> phi_bb33_12;
  TNode<IntPtrT> phi_bb33_13;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_8, &phi_bb33_10, &phi_bb33_11, &phi_bb33_12, &phi_bb33_13);
    ca_.Goto(&block25, phi_bb33_8, phi_bb33_10, phi_bb33_11, phi_bb33_12, phi_bb33_13);
  }

  TNode<Uint32T> phi_bb34_8;
  TNode<JSAny> phi_bb34_10;
  TNode<FixedArray> phi_bb34_11;
  TNode<IntPtrT> phi_bb34_12;
  TNode<IntPtrT> phi_bb34_13;
  TNode<IntPtrT> tmp52;
  TNode<BoolT> tmp53;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_8, &phi_bb34_10, &phi_bb34_11, &phi_bb34_12, &phi_bb34_13);
    tmp52 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp53 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb34_13}, TNode<IntPtrT>{tmp52});
    ca_.Branch(tmp53, &block94, std::vector<compiler::Node*>{phi_bb34_8, phi_bb34_10, phi_bb34_11, phi_bb34_12, phi_bb34_13, phi_bb34_13, phi_bb34_13}, &block95, std::vector<compiler::Node*>{phi_bb34_8, phi_bb34_10, phi_bb34_11, phi_bb34_12, phi_bb34_13, phi_bb34_13, phi_bb34_13});
  }

  TNode<Uint32T> phi_bb32_8;
  TNode<JSAny> phi_bb32_10;
  TNode<FixedArray> phi_bb32_11;
  TNode<IntPtrT> phi_bb32_12;
  TNode<IntPtrT> phi_bb32_13;
  TNode<JSReceiver> tmp54;
      TNode<JSAny> tmp57;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_8, &phi_bb32_10, &phi_bb32_11, &phi_bb32_12, &phi_bb32_13);
    compiler::CodeAssemblerLabel label55(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch56__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch56__label);
    tmp54 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp47}, &label55);
    }
    if (catch56__label.is_used()) {
      compiler::CodeAssemblerLabel catch56_skip(&ca_);
      ca_.Goto(&catch56_skip);
      ca_.Bind(&catch56__label, &tmp57);
      ca_.Goto(&block41, phi_bb32_8, phi_bb32_10, phi_bb32_11, phi_bb32_12, phi_bb32_13);
      ca_.Bind(&catch56_skip);
    }
    ca_.Goto(&block39, phi_bb32_8, phi_bb32_10, phi_bb32_11, phi_bb32_12, phi_bb32_13);
    if (label55.is_used()) {
      ca_.Bind(&label55);
      ca_.Goto(&block40, phi_bb32_8, phi_bb32_10, phi_bb32_11, phi_bb32_12, phi_bb32_13);
    }
  }

  TNode<Uint32T> phi_bb41_8;
  TNode<JSAny> phi_bb41_10;
  TNode<FixedArray> phi_bb41_11;
  TNode<IntPtrT> phi_bb41_12;
  TNode<IntPtrT> phi_bb41_13;
  TNode<Union<JSMessageObject, TheHole>> tmp58;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_8, &phi_bb41_10, &phi_bb41_11, &phi_bb41_12, &phi_bb41_13);
    tmp58 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block36, phi_bb41_8, phi_bb41_10, phi_bb41_11, phi_bb41_12, phi_bb41_13, tmp57, tmp58);
  }

  TNode<Uint32T> phi_bb40_8;
  TNode<JSAny> phi_bb40_10;
  TNode<FixedArray> phi_bb40_11;
  TNode<IntPtrT> phi_bb40_12;
  TNode<IntPtrT> phi_bb40_13;
      TNode<JSAny> tmp60;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_8, &phi_bb40_10, &phi_bb40_11, &phi_bb40_12, &phi_bb40_13);
    compiler::CodeAssemblerExceptionHandlerLabel catch59__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch59__label);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kNotIterable), TNode<Object>{tmp47});
    }
    if (catch59__label.is_used()) {
      compiler::CodeAssemblerLabel catch59_skip(&ca_);
      ca_.Bind(&catch59__label, &tmp60);
      ca_.Goto(&block42, phi_bb40_8, phi_bb40_10, phi_bb40_11, phi_bb40_12, phi_bb40_13);
    }
  }

  TNode<Uint32T> phi_bb39_8;
  TNode<JSAny> phi_bb39_10;
  TNode<FixedArray> phi_bb39_11;
  TNode<IntPtrT> phi_bb39_12;
  TNode<IntPtrT> phi_bb39_13;
  TNode<JSReceiver> tmp61;
  TNode<JSAny> tmp62;
      TNode<JSAny> tmp64;
  TNode<BoolT> tmp65;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_8, &phi_bb39_10, &phi_bb39_11, &phi_bb39_12, &phi_bb39_13);
    compiler::CodeAssemblerExceptionHandlerLabel catch63__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch63__label);
    std::tie(tmp61, tmp62) = GetIteratorFlattenable_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, String>>{tmp54}).Flatten();
    }
    if (catch63__label.is_used()) {
      compiler::CodeAssemblerLabel catch63_skip(&ca_);
      ca_.Goto(&catch63_skip);
      ca_.Bind(&catch63__label, &tmp64);
      ca_.Goto(&block43, phi_bb39_8, phi_bb39_10, phi_bb39_11, phi_bb39_12, phi_bb39_13);
      ca_.Bind(&catch63_skip);
    }
    tmp65 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb39_13}, TNode<IntPtrT>{phi_bb39_12});
    ca_.Branch(tmp65, &block53, std::vector<compiler::Node*>{phi_bb39_8, phi_bb39_10, phi_bb39_11, phi_bb39_12, phi_bb39_13}, &block54, std::vector<compiler::Node*>{phi_bb39_8, phi_bb39_10, phi_bb39_11, phi_bb39_12, phi_bb39_13});
  }

  TNode<Uint32T> phi_bb42_8;
  TNode<JSAny> phi_bb42_10;
  TNode<FixedArray> phi_bb42_11;
  TNode<IntPtrT> phi_bb42_12;
  TNode<IntPtrT> phi_bb42_13;
  TNode<Union<JSMessageObject, TheHole>> tmp66;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_8, &phi_bb42_10, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13);
    tmp66 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block36, phi_bb42_8, phi_bb42_10, phi_bb42_11, phi_bb42_12, phi_bb42_13, tmp60, tmp66);
  }

  TNode<Uint32T> phi_bb43_8;
  TNode<JSAny> phi_bb43_10;
  TNode<FixedArray> phi_bb43_11;
  TNode<IntPtrT> phi_bb43_12;
  TNode<IntPtrT> phi_bb43_13;
  TNode<Union<JSMessageObject, TheHole>> tmp67;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_8, &phi_bb43_10, &phi_bb43_11, &phi_bb43_12, &phi_bb43_13);
    tmp67 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block36, phi_bb43_8, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, tmp64, tmp67);
  }

  TNode<Uint32T> phi_bb36_8;
  TNode<JSAny> phi_bb36_10;
  TNode<FixedArray> phi_bb36_11;
  TNode<IntPtrT> phi_bb36_12;
  TNode<IntPtrT> phi_bb36_13;
  TNode<JSAny> phi_bb36_21;
  TNode<Union<JSMessageObject, TheHole>> phi_bb36_22;
  TNode<IntPtrT> tmp68;
  TNode<BoolT> tmp69;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_8, &phi_bb36_10, &phi_bb36_11, &phi_bb36_12, &phi_bb36_13, &phi_bb36_21, &phi_bb36_22);
    tmp68 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp69 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb36_13}, TNode<IntPtrT>{tmp68});
    ca_.Branch(tmp69, &block45, std::vector<compiler::Node*>{phi_bb36_8, phi_bb36_10, phi_bb36_11, phi_bb36_12, phi_bb36_13, phi_bb36_13, phi_bb36_13}, &block46, std::vector<compiler::Node*>{phi_bb36_8, phi_bb36_10, phi_bb36_11, phi_bb36_12, phi_bb36_13, phi_bb36_13, phi_bb36_13});
  }

  TNode<Uint32T> phi_bb46_8;
  TNode<JSAny> phi_bb46_10;
  TNode<FixedArray> phi_bb46_11;
  TNode<IntPtrT> phi_bb46_12;
  TNode<IntPtrT> phi_bb46_13;
  TNode<IntPtrT> phi_bb46_23;
  TNode<IntPtrT> phi_bb46_24;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_8, &phi_bb46_10, &phi_bb46_11, &phi_bb46_12, &phi_bb46_13, &phi_bb46_23, &phi_bb46_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb45_8;
  TNode<JSAny> phi_bb45_10;
  TNode<FixedArray> phi_bb45_11;
  TNode<IntPtrT> phi_bb45_12;
  TNode<IntPtrT> phi_bb45_13;
  TNode<IntPtrT> phi_bb45_23;
  TNode<IntPtrT> phi_bb45_24;
  TNode<IntPtrT> tmp70;
  TNode<BoolT> tmp71;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_8, &phi_bb45_10, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_23, &phi_bb45_24);
    tmp70 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp71 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb45_24}, TNode<IntPtrT>{tmp70});
    ca_.Branch(tmp71, &block47, std::vector<compiler::Node*>{phi_bb45_8, phi_bb45_10, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_23, phi_bb45_24}, &block48, std::vector<compiler::Node*>{phi_bb45_8, phi_bb45_10, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_23, phi_bb45_24});
  }

  TNode<Uint32T> phi_bb48_8;
  TNode<JSAny> phi_bb48_10;
  TNode<FixedArray> phi_bb48_11;
  TNode<IntPtrT> phi_bb48_12;
  TNode<IntPtrT> phi_bb48_13;
  TNode<IntPtrT> phi_bb48_23;
  TNode<IntPtrT> phi_bb48_24;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_8, &phi_bb48_10, &phi_bb48_11, &phi_bb48_12, &phi_bb48_13, &phi_bb48_23, &phi_bb48_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb47_8;
  TNode<JSAny> phi_bb47_10;
  TNode<FixedArray> phi_bb47_11;
  TNode<IntPtrT> phi_bb47_12;
  TNode<IntPtrT> phi_bb47_13;
  TNode<IntPtrT> phi_bb47_23;
  TNode<IntPtrT> phi_bb47_24;
  TNode<BoolT> tmp72;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_8, &phi_bb47_10, &phi_bb47_11, &phi_bb47_12, &phi_bb47_13, &phi_bb47_23, &phi_bb47_24);
    tmp72 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb47_24}, TNode<IntPtrT>{phi_bb47_13});
    ca_.Branch(tmp72, &block49, std::vector<compiler::Node*>{phi_bb47_8, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_23, phi_bb47_24}, &block50, std::vector<compiler::Node*>{phi_bb47_8, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_23, phi_bb47_24});
  }

  TNode<Uint32T> phi_bb50_8;
  TNode<JSAny> phi_bb50_10;
  TNode<FixedArray> phi_bb50_11;
  TNode<IntPtrT> phi_bb50_12;
  TNode<IntPtrT> phi_bb50_13;
  TNode<IntPtrT> phi_bb50_23;
  TNode<IntPtrT> phi_bb50_24;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_8, &phi_bb50_10, &phi_bb50_11, &phi_bb50_12, &phi_bb50_13, &phi_bb50_23, &phi_bb50_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb49_8;
  TNode<JSAny> phi_bb49_10;
  TNode<FixedArray> phi_bb49_11;
  TNode<IntPtrT> phi_bb49_12;
  TNode<IntPtrT> phi_bb49_13;
  TNode<IntPtrT> phi_bb49_23;
  TNode<IntPtrT> phi_bb49_24;
  TNode<IntPtrT> tmp73;
  TNode<TheHole> tmp74;
  TNode<FixedArray> tmp75;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_8, &phi_bb49_10, &phi_bb49_11, &phi_bb49_12, &phi_bb49_13, &phi_bb49_23, &phi_bb49_24);
    tmp73 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp74 = TheHole_0(state_);
    tmp75 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb49_11}, TNode<IntPtrT>{tmp73}, TNode<IntPtrT>{phi_bb49_13}, TNode<IntPtrT>{phi_bb49_24}, TNode<Hole>{tmp74});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp75}, false);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp44});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb36_21, phi_bb36_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb54_8;
  TNode<JSAny> phi_bb54_10;
  TNode<FixedArray> phi_bb54_11;
  TNode<IntPtrT> phi_bb54_12;
  TNode<IntPtrT> phi_bb54_13;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_8, &phi_bb54_10, &phi_bb54_11, &phi_bb54_12, &phi_bb54_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb53_8;
  TNode<JSAny> phi_bb53_10;
  TNode<FixedArray> phi_bb53_11;
  TNode<IntPtrT> phi_bb53_12;
  TNode<IntPtrT> phi_bb53_13;
  TNode<BoolT> tmp76;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_8, &phi_bb53_10, &phi_bb53_11, &phi_bb53_12, &phi_bb53_13);
    tmp76 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb53_12}, TNode<IntPtrT>{phi_bb53_13});
    ca_.Branch(tmp76, &block55, std::vector<compiler::Node*>{phi_bb53_8, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13}, &block56, std::vector<compiler::Node*>{phi_bb53_8, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13});
  }

  TNode<Uint32T> phi_bb55_8;
  TNode<JSAny> phi_bb55_10;
  TNode<FixedArray> phi_bb55_11;
  TNode<IntPtrT> phi_bb55_12;
  TNode<IntPtrT> phi_bb55_13;
  TNode<IntPtrT> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<IntPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<BoolT> tmp83;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_8, &phi_bb55_10, &phi_bb55_11, &phi_bb55_12, &phi_bb55_13);
    tmp77 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp78 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb55_12}, TNode<IntPtrT>{tmp77});
    tmp79 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb55_12}, TNode<IntPtrT>{tmp78});
    tmp80 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp81 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp79}, TNode<IntPtrT>{tmp80});
    tmp82 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp83 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb55_13}, TNode<IntPtrT>{tmp82});
    ca_.Branch(tmp83, &block58, std::vector<compiler::Node*>{phi_bb55_8, phi_bb55_10, phi_bb55_11, phi_bb55_13}, &block59, std::vector<compiler::Node*>{phi_bb55_8, phi_bb55_10, phi_bb55_11, phi_bb55_13});
  }

  TNode<Uint32T> phi_bb59_8;
  TNode<JSAny> phi_bb59_10;
  TNode<FixedArray> phi_bb59_11;
  TNode<IntPtrT> phi_bb59_13;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_8, &phi_bb59_10, &phi_bb59_11, &phi_bb59_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb58_8;
  TNode<JSAny> phi_bb58_10;
  TNode<FixedArray> phi_bb58_11;
  TNode<IntPtrT> phi_bb58_13;
  TNode<IntPtrT> tmp84;
  TNode<BoolT> tmp85;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_8, &phi_bb58_10, &phi_bb58_11, &phi_bb58_13);
    tmp84 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp85 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp81}, TNode<IntPtrT>{tmp84});
    ca_.Branch(tmp85, &block60, std::vector<compiler::Node*>{phi_bb58_8, phi_bb58_10, phi_bb58_11, phi_bb58_13}, &block61, std::vector<compiler::Node*>{phi_bb58_8, phi_bb58_10, phi_bb58_11, phi_bb58_13});
  }

  TNode<Uint32T> phi_bb61_8;
  TNode<JSAny> phi_bb61_10;
  TNode<FixedArray> phi_bb61_11;
  TNode<IntPtrT> phi_bb61_13;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_8, &phi_bb61_10, &phi_bb61_11, &phi_bb61_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb60_8;
  TNode<JSAny> phi_bb60_10;
  TNode<FixedArray> phi_bb60_11;
  TNode<IntPtrT> phi_bb60_13;
  TNode<BoolT> tmp86;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_8, &phi_bb60_10, &phi_bb60_11, &phi_bb60_13);
    tmp86 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp81}, TNode<IntPtrT>{phi_bb60_13});
    ca_.Branch(tmp86, &block62, std::vector<compiler::Node*>{phi_bb60_8, phi_bb60_10, phi_bb60_11, phi_bb60_13}, &block63, std::vector<compiler::Node*>{phi_bb60_8, phi_bb60_10, phi_bb60_11, phi_bb60_13});
  }

  TNode<Uint32T> phi_bb63_8;
  TNode<JSAny> phi_bb63_10;
  TNode<FixedArray> phi_bb63_11;
  TNode<IntPtrT> phi_bb63_13;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_8, &phi_bb63_10, &phi_bb63_11, &phi_bb63_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb62_8;
  TNode<JSAny> phi_bb62_10;
  TNode<FixedArray> phi_bb62_11;
  TNode<IntPtrT> phi_bb62_13;
  TNode<IntPtrT> tmp87;
  TNode<TheHole> tmp88;
  TNode<FixedArray> tmp89;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_8, &phi_bb62_10, &phi_bb62_11, &phi_bb62_13);
    tmp87 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp88 = TheHole_0(state_);
    tmp89 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb62_11}, TNode<IntPtrT>{tmp87}, TNode<IntPtrT>{phi_bb62_13}, TNode<IntPtrT>{tmp81}, TNode<Hole>{tmp88});
    ca_.Goto(&block56, phi_bb62_8, phi_bb62_10, tmp89, tmp81, phi_bb62_13);
  }

  TNode<Uint32T> phi_bb56_8;
  TNode<JSAny> phi_bb56_10;
  TNode<FixedArray> phi_bb56_11;
  TNode<IntPtrT> phi_bb56_12;
  TNode<IntPtrT> phi_bb56_13;
  TNode<Union<HeapObject, TaggedIndex>> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<IntPtrT> tmp93;
  TNode<IntPtrT> tmp94;
  TNode<UintPtrT> tmp95;
  TNode<UintPtrT> tmp96;
  TNode<BoolT> tmp97;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_8, &phi_bb56_10, &phi_bb56_11, &phi_bb56_12, &phi_bb56_13);
    std::tie(tmp90, tmp91, tmp92) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb56_11}).Flatten();
    tmp93 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp94 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb56_13}, TNode<IntPtrT>{tmp93});
    tmp95 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb56_13});
    tmp96 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp92});
    tmp97 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp95}, TNode<UintPtrT>{tmp96});
    ca_.Branch(tmp97, &block68, std::vector<compiler::Node*>{phi_bb56_8, phi_bb56_10, phi_bb56_11, phi_bb56_12, phi_bb56_11, phi_bb56_13, phi_bb56_13, phi_bb56_13, phi_bb56_13}, &block69, std::vector<compiler::Node*>{phi_bb56_8, phi_bb56_10, phi_bb56_11, phi_bb56_12, phi_bb56_11, phi_bb56_13, phi_bb56_13, phi_bb56_13, phi_bb56_13});
  }

  TNode<Uint32T> phi_bb68_8;
  TNode<JSAny> phi_bb68_10;
  TNode<FixedArray> phi_bb68_11;
  TNode<IntPtrT> phi_bb68_12;
  TNode<FixedArray> phi_bb68_23;
  TNode<IntPtrT> phi_bb68_27;
  TNode<IntPtrT> phi_bb68_28;
  TNode<IntPtrT> phi_bb68_32;
  TNode<IntPtrT> phi_bb68_33;
  TNode<IntPtrT> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<Union<HeapObject, TaggedIndex>> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<BoolT> tmp102;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_8, &phi_bb68_10, &phi_bb68_11, &phi_bb68_12, &phi_bb68_23, &phi_bb68_27, &phi_bb68_28, &phi_bb68_32, &phi_bb68_33);
    tmp98 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb68_33});
    tmp99 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp91}, TNode<IntPtrT>{tmp98});
    std::tie(tmp100, tmp101) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp90}, TNode<IntPtrT>{tmp99}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp100, tmp101}, tmp61);
    tmp102 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp94}, TNode<IntPtrT>{phi_bb68_12});
    ca_.Branch(tmp102, &block74, std::vector<compiler::Node*>{phi_bb68_8, phi_bb68_10, phi_bb68_11, phi_bb68_12}, &block75, std::vector<compiler::Node*>{phi_bb68_8, phi_bb68_10, phi_bb68_11, phi_bb68_12});
  }

  TNode<Uint32T> phi_bb69_8;
  TNode<JSAny> phi_bb69_10;
  TNode<FixedArray> phi_bb69_11;
  TNode<IntPtrT> phi_bb69_12;
  TNode<FixedArray> phi_bb69_23;
  TNode<IntPtrT> phi_bb69_27;
  TNode<IntPtrT> phi_bb69_28;
  TNode<IntPtrT> phi_bb69_32;
  TNode<IntPtrT> phi_bb69_33;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_8, &phi_bb69_10, &phi_bb69_11, &phi_bb69_12, &phi_bb69_23, &phi_bb69_27, &phi_bb69_28, &phi_bb69_32, &phi_bb69_33);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb75_8;
  TNode<JSAny> phi_bb75_10;
  TNode<FixedArray> phi_bb75_11;
  TNode<IntPtrT> phi_bb75_12;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_8, &phi_bb75_10, &phi_bb75_11, &phi_bb75_12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb74_8;
  TNode<JSAny> phi_bb74_10;
  TNode<FixedArray> phi_bb74_11;
  TNode<IntPtrT> phi_bb74_12;
  TNode<BoolT> tmp103;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_8, &phi_bb74_10, &phi_bb74_11, &phi_bb74_12);
    tmp103 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb74_12}, TNode<IntPtrT>{tmp94});
    ca_.Branch(tmp103, &block76, std::vector<compiler::Node*>{phi_bb74_8, phi_bb74_10, phi_bb74_11, phi_bb74_12}, &block77, std::vector<compiler::Node*>{phi_bb74_8, phi_bb74_10, phi_bb74_11, phi_bb74_12});
  }

  TNode<Uint32T> phi_bb76_8;
  TNode<JSAny> phi_bb76_10;
  TNode<FixedArray> phi_bb76_11;
  TNode<IntPtrT> phi_bb76_12;
  TNode<IntPtrT> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<BoolT> tmp110;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_8, &phi_bb76_10, &phi_bb76_11, &phi_bb76_12);
    tmp104 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp105 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb76_12}, TNode<IntPtrT>{tmp104});
    tmp106 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb76_12}, TNode<IntPtrT>{tmp105});
    tmp107 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp108 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp106}, TNode<IntPtrT>{tmp107});
    tmp109 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp110 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp94}, TNode<IntPtrT>{tmp109});
    ca_.Branch(tmp110, &block79, std::vector<compiler::Node*>{phi_bb76_8, phi_bb76_10, phi_bb76_11}, &block80, std::vector<compiler::Node*>{phi_bb76_8, phi_bb76_10, phi_bb76_11});
  }

  TNode<Uint32T> phi_bb80_8;
  TNode<JSAny> phi_bb80_10;
  TNode<FixedArray> phi_bb80_11;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_8, &phi_bb80_10, &phi_bb80_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb79_8;
  TNode<JSAny> phi_bb79_10;
  TNode<FixedArray> phi_bb79_11;
  TNode<IntPtrT> tmp111;
  TNode<BoolT> tmp112;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_8, &phi_bb79_10, &phi_bb79_11);
    tmp111 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp112 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp108}, TNode<IntPtrT>{tmp111});
    ca_.Branch(tmp112, &block81, std::vector<compiler::Node*>{phi_bb79_8, phi_bb79_10, phi_bb79_11}, &block82, std::vector<compiler::Node*>{phi_bb79_8, phi_bb79_10, phi_bb79_11});
  }

  TNode<Uint32T> phi_bb82_8;
  TNode<JSAny> phi_bb82_10;
  TNode<FixedArray> phi_bb82_11;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_8, &phi_bb82_10, &phi_bb82_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb81_8;
  TNode<JSAny> phi_bb81_10;
  TNode<FixedArray> phi_bb81_11;
  TNode<BoolT> tmp113;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_8, &phi_bb81_10, &phi_bb81_11);
    tmp113 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp108}, TNode<IntPtrT>{tmp94});
    ca_.Branch(tmp113, &block83, std::vector<compiler::Node*>{phi_bb81_8, phi_bb81_10, phi_bb81_11}, &block84, std::vector<compiler::Node*>{phi_bb81_8, phi_bb81_10, phi_bb81_11});
  }

  TNode<Uint32T> phi_bb84_8;
  TNode<JSAny> phi_bb84_10;
  TNode<FixedArray> phi_bb84_11;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_8, &phi_bb84_10, &phi_bb84_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb83_8;
  TNode<JSAny> phi_bb83_10;
  TNode<FixedArray> phi_bb83_11;
  TNode<IntPtrT> tmp114;
  TNode<TheHole> tmp115;
  TNode<FixedArray> tmp116;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_8, &phi_bb83_10, &phi_bb83_11);
    tmp114 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp115 = TheHole_0(state_);
    tmp116 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb83_11}, TNode<IntPtrT>{tmp114}, TNode<IntPtrT>{tmp94}, TNode<IntPtrT>{tmp108}, TNode<Hole>{tmp115});
    ca_.Goto(&block77, phi_bb83_8, phi_bb83_10, tmp116, tmp108);
  }

  TNode<Uint32T> phi_bb77_8;
  TNode<JSAny> phi_bb77_10;
  TNode<FixedArray> phi_bb77_11;
  TNode<IntPtrT> phi_bb77_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<IntPtrT> tmp119;
  TNode<IntPtrT> tmp120;
  TNode<IntPtrT> tmp121;
  TNode<UintPtrT> tmp122;
  TNode<UintPtrT> tmp123;
  TNode<BoolT> tmp124;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_8, &phi_bb77_10, &phi_bb77_11, &phi_bb77_12);
    std::tie(tmp117, tmp118, tmp119) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb77_11}).Flatten();
    tmp120 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp121 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp94}, TNode<IntPtrT>{tmp120});
    tmp122 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp94});
    tmp123 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp119});
    tmp124 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp122}, TNode<UintPtrT>{tmp123});
    ca_.Branch(tmp124, &block89, std::vector<compiler::Node*>{phi_bb77_8, phi_bb77_10, phi_bb77_11, phi_bb77_12, phi_bb77_11}, &block90, std::vector<compiler::Node*>{phi_bb77_8, phi_bb77_10, phi_bb77_11, phi_bb77_12, phi_bb77_11});
  }

  TNode<Uint32T> phi_bb89_8;
  TNode<JSAny> phi_bb89_10;
  TNode<FixedArray> phi_bb89_11;
  TNode<IntPtrT> phi_bb89_12;
  TNode<FixedArray> phi_bb89_23;
  TNode<IntPtrT> tmp125;
  TNode<IntPtrT> tmp126;
  TNode<Union<HeapObject, TaggedIndex>> tmp127;
  TNode<IntPtrT> tmp128;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_8, &phi_bb89_10, &phi_bb89_11, &phi_bb89_12, &phi_bb89_23);
    tmp125 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp94});
    tmp126 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp118}, TNode<IntPtrT>{tmp125});
    std::tie(tmp127, tmp128) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp117}, TNode<IntPtrT>{tmp126}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp127, tmp128}, tmp62);
    ca_.Goto(&block31, phi_bb89_8, phi_bb89_10, phi_bb89_11, phi_bb89_12, tmp121);
  }

  TNode<Uint32T> phi_bb90_8;
  TNode<JSAny> phi_bb90_10;
  TNode<FixedArray> phi_bb90_11;
  TNode<IntPtrT> phi_bb90_12;
  TNode<FixedArray> phi_bb90_23;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_8, &phi_bb90_10, &phi_bb90_11, &phi_bb90_12, &phi_bb90_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb30_8;
  TNode<JSAny> phi_bb30_10;
  TNode<FixedArray> phi_bb30_11;
  TNode<IntPtrT> phi_bb30_12;
  TNode<IntPtrT> phi_bb30_13;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_8, &phi_bb30_10, &phi_bb30_11, &phi_bb30_12, &phi_bb30_13);
    ca_.Goto(&block25, phi_bb30_8, phi_bb30_10, phi_bb30_11, phi_bb30_12, phi_bb30_13);
  }

  TNode<Uint32T> phi_bb95_8;
  TNode<JSAny> phi_bb95_10;
  TNode<FixedArray> phi_bb95_11;
  TNode<IntPtrT> phi_bb95_12;
  TNode<IntPtrT> phi_bb95_13;
  TNode<IntPtrT> phi_bb95_18;
  TNode<IntPtrT> phi_bb95_19;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_8, &phi_bb95_10, &phi_bb95_11, &phi_bb95_12, &phi_bb95_13, &phi_bb95_18, &phi_bb95_19);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb94_8;
  TNode<JSAny> phi_bb94_10;
  TNode<FixedArray> phi_bb94_11;
  TNode<IntPtrT> phi_bb94_12;
  TNode<IntPtrT> phi_bb94_13;
  TNode<IntPtrT> phi_bb94_18;
  TNode<IntPtrT> phi_bb94_19;
  TNode<IntPtrT> tmp129;
  TNode<BoolT> tmp130;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_8, &phi_bb94_10, &phi_bb94_11, &phi_bb94_12, &phi_bb94_13, &phi_bb94_18, &phi_bb94_19);
    tmp129 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp130 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb94_19}, TNode<IntPtrT>{tmp129});
    ca_.Branch(tmp130, &block96, std::vector<compiler::Node*>{phi_bb94_8, phi_bb94_10, phi_bb94_11, phi_bb94_12, phi_bb94_13, phi_bb94_18, phi_bb94_19}, &block97, std::vector<compiler::Node*>{phi_bb94_8, phi_bb94_10, phi_bb94_11, phi_bb94_12, phi_bb94_13, phi_bb94_18, phi_bb94_19});
  }

  TNode<Uint32T> phi_bb97_8;
  TNode<JSAny> phi_bb97_10;
  TNode<FixedArray> phi_bb97_11;
  TNode<IntPtrT> phi_bb97_12;
  TNode<IntPtrT> phi_bb97_13;
  TNode<IntPtrT> phi_bb97_18;
  TNode<IntPtrT> phi_bb97_19;
  if (block97.is_used()) {
    ca_.Bind(&block97, &phi_bb97_8, &phi_bb97_10, &phi_bb97_11, &phi_bb97_12, &phi_bb97_13, &phi_bb97_18, &phi_bb97_19);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb96_8;
  TNode<JSAny> phi_bb96_10;
  TNode<FixedArray> phi_bb96_11;
  TNode<IntPtrT> phi_bb96_12;
  TNode<IntPtrT> phi_bb96_13;
  TNode<IntPtrT> phi_bb96_18;
  TNode<IntPtrT> phi_bb96_19;
  TNode<BoolT> tmp131;
  if (block96.is_used()) {
    ca_.Bind(&block96, &phi_bb96_8, &phi_bb96_10, &phi_bb96_11, &phi_bb96_12, &phi_bb96_13, &phi_bb96_18, &phi_bb96_19);
    tmp131 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb96_19}, TNode<IntPtrT>{phi_bb96_13});
    ca_.Branch(tmp131, &block98, std::vector<compiler::Node*>{phi_bb96_8, phi_bb96_10, phi_bb96_11, phi_bb96_12, phi_bb96_13, phi_bb96_18, phi_bb96_19}, &block99, std::vector<compiler::Node*>{phi_bb96_8, phi_bb96_10, phi_bb96_11, phi_bb96_12, phi_bb96_13, phi_bb96_18, phi_bb96_19});
  }

  TNode<Uint32T> phi_bb99_8;
  TNode<JSAny> phi_bb99_10;
  TNode<FixedArray> phi_bb99_11;
  TNode<IntPtrT> phi_bb99_12;
  TNode<IntPtrT> phi_bb99_13;
  TNode<IntPtrT> phi_bb99_18;
  TNode<IntPtrT> phi_bb99_19;
  if (block99.is_used()) {
    ca_.Bind(&block99, &phi_bb99_8, &phi_bb99_10, &phi_bb99_11, &phi_bb99_12, &phi_bb99_13, &phi_bb99_18, &phi_bb99_19);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb98_8;
  TNode<JSAny> phi_bb98_10;
  TNode<FixedArray> phi_bb98_11;
  TNode<IntPtrT> phi_bb98_12;
  TNode<IntPtrT> phi_bb98_13;
  TNode<IntPtrT> phi_bb98_18;
  TNode<IntPtrT> phi_bb98_19;
  TNode<IntPtrT> tmp132;
  TNode<TheHole> tmp133;
  TNode<FixedArray> tmp134;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_8, &phi_bb98_10, &phi_bb98_11, &phi_bb98_12, &phi_bb98_13, &phi_bb98_18, &phi_bb98_19);
    tmp132 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp133 = TheHole_0(state_);
    tmp134 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb98_11}, TNode<IntPtrT>{tmp132}, TNode<IntPtrT>{phi_bb98_13}, TNode<IntPtrT>{phi_bb98_19}, TNode<Hole>{tmp133});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp134}, false);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp50.value(), tmp51.value());
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb25_8;
  TNode<JSAny> phi_bb25_10;
  TNode<FixedArray> phi_bb25_11;
  TNode<IntPtrT> phi_bb25_12;
  TNode<IntPtrT> phi_bb25_13;
  TNode<IntPtrT> tmp135;
  TNode<IntPtrT> tmp136;
  TNode<Uint32T> tmp137;
  TNode<BoolT> tmp138;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_8, &phi_bb25_10, &phi_bb25_11, &phi_bb25_12, &phi_bb25_13);
    tmp135 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp136 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{phi_bb25_13}, TNode<IntPtrT>{tmp135});
    tmp137 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kLongest));
    tmp138 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{phi_bb25_8}, TNode<Uint32T>{tmp137});
    ca_.Branch(tmp138, &block100, std::vector<compiler::Node*>{phi_bb25_8, phi_bb25_10, phi_bb25_11, phi_bb25_12, phi_bb25_13}, &block101, std::vector<compiler::Node*>{phi_bb25_8, phi_bb25_10, phi_bb25_11, phi_bb25_12, phi_bb25_13, tmp42});
  }

  TNode<Uint32T> phi_bb100_8;
  TNode<JSAny> phi_bb100_10;
  TNode<FixedArray> phi_bb100_11;
  TNode<IntPtrT> phi_bb100_12;
  TNode<IntPtrT> phi_bb100_13;
  TNode<Undefined> tmp139;
  TNode<Undefined> tmp140;
  TNode<FixedArray> tmp141;
  TNode<Undefined> tmp142;
  TNode<BoolT> tmp143;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_8, &phi_bb100_10, &phi_bb100_11, &phi_bb100_12, &phi_bb100_13);
    tmp139 = Undefined_0(state_);
    std::tie(tmp140) = ConstantIterator_Undefined_0(state_, TNode<Undefined>{tmp139}).Flatten();
    tmp141 = NewFixedArray_ConstantIterator_Undefined_0(state_, TNode<IntPtrT>{tmp136}, TorqueStructConstantIterator_Undefined_0{TNode<Undefined>{tmp140}});
    tmp142 = Undefined_0(state_);
    tmp143 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{phi_bb100_10}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp142});
    ca_.Branch(tmp143, &block102, std::vector<compiler::Node*>{phi_bb100_8, phi_bb100_10, phi_bb100_11, phi_bb100_12, phi_bb100_13}, &block103, std::vector<compiler::Node*>{phi_bb100_8, phi_bb100_10, phi_bb100_11, phi_bb100_12, phi_bb100_13});
  }

  TNode<Uint32T> phi_bb102_8;
  TNode<JSAny> phi_bb102_10;
  TNode<FixedArray> phi_bb102_11;
  TNode<IntPtrT> phi_bb102_12;
  TNode<IntPtrT> phi_bb102_13;
  TNode<JSReceiver> tmp144;
  TNode<JSAny> tmp145;
      TNode<JSAny> tmp147;
  TNode<BoolT> tmp148;
  TNode<IntPtrT> tmp149;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_8, &phi_bb102_10, &phi_bb102_11, &phi_bb102_12, &phi_bb102_13);
    compiler::CodeAssemblerExceptionHandlerLabel catch146__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch146__label);
    std::tie(tmp144, tmp145) = IteratorBuiltinsAssembler(state_).GetIterator(TNode<Context>{parameter0}, TNode<JSAny>{phi_bb102_10}).Flatten();
    }
    if (catch146__label.is_used()) {
      compiler::CodeAssemblerLabel catch146_skip(&ca_);
      ca_.Goto(&catch146_skip);
      ca_.Bind(&catch146__label, &tmp147);
      ca_.Goto(&block106, phi_bb102_8, phi_bb102_10, phi_bb102_11, phi_bb102_12, phi_bb102_13, phi_bb102_10);
      ca_.Bind(&catch146_skip);
    }
    tmp148 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp149 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block116, phi_bb102_8, phi_bb102_10, phi_bb102_11, phi_bb102_12, phi_bb102_13, tmp148, tmp149);
  }

  TNode<Uint32T> phi_bb106_8;
  TNode<JSAny> phi_bb106_10;
  TNode<FixedArray> phi_bb106_11;
  TNode<IntPtrT> phi_bb106_12;
  TNode<IntPtrT> phi_bb106_13;
  TNode<JSAny> phi_bb106_19;
  TNode<Union<JSMessageObject, TheHole>> tmp150;
  TNode<IntPtrT> tmp151;
  TNode<BoolT> tmp152;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_8, &phi_bb106_10, &phi_bb106_11, &phi_bb106_12, &phi_bb106_13, &phi_bb106_19);
    tmp150 = GetAndResetPendingMessage_0(state_);
    tmp151 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp152 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb106_13}, TNode<IntPtrT>{tmp151});
    ca_.Branch(tmp152, &block108, std::vector<compiler::Node*>{phi_bb106_8, phi_bb106_10, phi_bb106_11, phi_bb106_12, phi_bb106_13, phi_bb106_13, phi_bb106_13}, &block109, std::vector<compiler::Node*>{phi_bb106_8, phi_bb106_10, phi_bb106_11, phi_bb106_12, phi_bb106_13, phi_bb106_13, phi_bb106_13});
  }

  TNode<Uint32T> phi_bb109_8;
  TNode<JSAny> phi_bb109_10;
  TNode<FixedArray> phi_bb109_11;
  TNode<IntPtrT> phi_bb109_12;
  TNode<IntPtrT> phi_bb109_13;
  TNode<IntPtrT> phi_bb109_21;
  TNode<IntPtrT> phi_bb109_22;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_8, &phi_bb109_10, &phi_bb109_11, &phi_bb109_12, &phi_bb109_13, &phi_bb109_21, &phi_bb109_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb108_8;
  TNode<JSAny> phi_bb108_10;
  TNode<FixedArray> phi_bb108_11;
  TNode<IntPtrT> phi_bb108_12;
  TNode<IntPtrT> phi_bb108_13;
  TNode<IntPtrT> phi_bb108_21;
  TNode<IntPtrT> phi_bb108_22;
  TNode<IntPtrT> tmp153;
  TNode<BoolT> tmp154;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_8, &phi_bb108_10, &phi_bb108_11, &phi_bb108_12, &phi_bb108_13, &phi_bb108_21, &phi_bb108_22);
    tmp153 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp154 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb108_22}, TNode<IntPtrT>{tmp153});
    ca_.Branch(tmp154, &block110, std::vector<compiler::Node*>{phi_bb108_8, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_13, phi_bb108_21, phi_bb108_22}, &block111, std::vector<compiler::Node*>{phi_bb108_8, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_13, phi_bb108_21, phi_bb108_22});
  }

  TNode<Uint32T> phi_bb111_8;
  TNode<JSAny> phi_bb111_10;
  TNode<FixedArray> phi_bb111_11;
  TNode<IntPtrT> phi_bb111_12;
  TNode<IntPtrT> phi_bb111_13;
  TNode<IntPtrT> phi_bb111_21;
  TNode<IntPtrT> phi_bb111_22;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_8, &phi_bb111_10, &phi_bb111_11, &phi_bb111_12, &phi_bb111_13, &phi_bb111_21, &phi_bb111_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb110_8;
  TNode<JSAny> phi_bb110_10;
  TNode<FixedArray> phi_bb110_11;
  TNode<IntPtrT> phi_bb110_12;
  TNode<IntPtrT> phi_bb110_13;
  TNode<IntPtrT> phi_bb110_21;
  TNode<IntPtrT> phi_bb110_22;
  TNode<BoolT> tmp155;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_8, &phi_bb110_10, &phi_bb110_11, &phi_bb110_12, &phi_bb110_13, &phi_bb110_21, &phi_bb110_22);
    tmp155 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb110_22}, TNode<IntPtrT>{phi_bb110_13});
    ca_.Branch(tmp155, &block112, std::vector<compiler::Node*>{phi_bb110_8, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_21, phi_bb110_22}, &block113, std::vector<compiler::Node*>{phi_bb110_8, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_21, phi_bb110_22});
  }

  TNode<Uint32T> phi_bb113_8;
  TNode<JSAny> phi_bb113_10;
  TNode<FixedArray> phi_bb113_11;
  TNode<IntPtrT> phi_bb113_12;
  TNode<IntPtrT> phi_bb113_13;
  TNode<IntPtrT> phi_bb113_21;
  TNode<IntPtrT> phi_bb113_22;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_8, &phi_bb113_10, &phi_bb113_11, &phi_bb113_12, &phi_bb113_13, &phi_bb113_21, &phi_bb113_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb112_8;
  TNode<JSAny> phi_bb112_10;
  TNode<FixedArray> phi_bb112_11;
  TNode<IntPtrT> phi_bb112_12;
  TNode<IntPtrT> phi_bb112_13;
  TNode<IntPtrT> phi_bb112_21;
  TNode<IntPtrT> phi_bb112_22;
  TNode<IntPtrT> tmp156;
  TNode<TheHole> tmp157;
  TNode<FixedArray> tmp158;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_8, &phi_bb112_10, &phi_bb112_11, &phi_bb112_12, &phi_bb112_13, &phi_bb112_21, &phi_bb112_22);
    tmp156 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp157 = TheHole_0(state_);
    tmp158 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb112_11}, TNode<IntPtrT>{tmp156}, TNode<IntPtrT>{phi_bb112_13}, TNode<IntPtrT>{phi_bb112_22}, TNode<Hole>{tmp157});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp158}, false);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp147, tmp150);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb116_8;
  TNode<JSAny> phi_bb116_10;
  TNode<FixedArray> phi_bb116_11;
  TNode<IntPtrT> phi_bb116_12;
  TNode<IntPtrT> phi_bb116_13;
  TNode<BoolT> phi_bb116_19;
  TNode<IntPtrT> phi_bb116_20;
  TNode<BoolT> tmp159;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_8, &phi_bb116_10, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13, &phi_bb116_19, &phi_bb116_20);
    tmp159 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb116_20}, TNode<IntPtrT>{tmp136});
    ca_.Branch(tmp159, &block114, std::vector<compiler::Node*>{phi_bb116_8, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_19, phi_bb116_20}, &block115, std::vector<compiler::Node*>{phi_bb116_8, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_19, phi_bb116_20});
  }

  TNode<Uint32T> phi_bb114_8;
  TNode<JSAny> phi_bb114_10;
  TNode<FixedArray> phi_bb114_11;
  TNode<IntPtrT> phi_bb114_12;
  TNode<IntPtrT> phi_bb114_13;
  TNode<BoolT> phi_bb114_19;
  TNode<IntPtrT> phi_bb114_20;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_8, &phi_bb114_10, &phi_bb114_11, &phi_bb114_12, &phi_bb114_13, &phi_bb114_19, &phi_bb114_20);
    ca_.Branch(phi_bb114_19, &block118, std::vector<compiler::Node*>{phi_bb114_8, phi_bb114_10, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_19, phi_bb114_20}, &block119, std::vector<compiler::Node*>{phi_bb114_8, phi_bb114_10, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_19, phi_bb114_20});
  }

  TNode<Uint32T> phi_bb118_8;
  TNode<JSAny> phi_bb118_10;
  TNode<FixedArray> phi_bb118_11;
  TNode<IntPtrT> phi_bb118_12;
  TNode<IntPtrT> phi_bb118_13;
  TNode<BoolT> phi_bb118_19;
  TNode<IntPtrT> phi_bb118_20;
  TNode<Union<HeapObject, TaggedIndex>> tmp160;
  TNode<IntPtrT> tmp161;
  TNode<IntPtrT> tmp162;
  TNode<UintPtrT> tmp163;
  TNode<UintPtrT> tmp164;
  TNode<BoolT> tmp165;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_8, &phi_bb118_10, &phi_bb118_11, &phi_bb118_12, &phi_bb118_13, &phi_bb118_19, &phi_bb118_20);
    std::tie(tmp160, tmp161, tmp162) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp141}).Flatten();
    tmp163 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb118_20});
    tmp164 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp162});
    tmp165 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp163}, TNode<UintPtrT>{tmp164});
    ca_.Branch(tmp165, &block128, std::vector<compiler::Node*>{phi_bb118_8, phi_bb118_10, phi_bb118_11, phi_bb118_12, phi_bb118_13, phi_bb118_19, phi_bb118_20, phi_bb118_20, phi_bb118_20, phi_bb118_20, phi_bb118_20}, &block129, std::vector<compiler::Node*>{phi_bb118_8, phi_bb118_10, phi_bb118_11, phi_bb118_12, phi_bb118_13, phi_bb118_19, phi_bb118_20, phi_bb118_20, phi_bb118_20, phi_bb118_20, phi_bb118_20});
  }

  TNode<Uint32T> phi_bb128_8;
  TNode<JSAny> phi_bb128_10;
  TNode<FixedArray> phi_bb128_11;
  TNode<IntPtrT> phi_bb128_12;
  TNode<IntPtrT> phi_bb128_13;
  TNode<BoolT> phi_bb128_19;
  TNode<IntPtrT> phi_bb128_20;
  TNode<IntPtrT> phi_bb128_25;
  TNode<IntPtrT> phi_bb128_26;
  TNode<IntPtrT> phi_bb128_30;
  TNode<IntPtrT> phi_bb128_31;
  TNode<IntPtrT> tmp166;
  TNode<IntPtrT> tmp167;
  TNode<Union<HeapObject, TaggedIndex>> tmp168;
  TNode<IntPtrT> tmp169;
  TNode<JSAny> tmp170;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp173(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp174(&ca_);
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_8, &phi_bb128_10, &phi_bb128_11, &phi_bb128_12, &phi_bb128_13, &phi_bb128_19, &phi_bb128_20, &phi_bb128_25, &phi_bb128_26, &phi_bb128_30, &phi_bb128_31);
    tmp166 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb128_31});
    tmp167 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp161}, TNode<IntPtrT>{tmp166});
    std::tie(tmp168, tmp169) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp160}, TNode<IntPtrT>{tmp167}).Flatten();
    compiler::CodeAssemblerLabel label171(&ca_);
    compiler::CodeAssemblerLabel label172(&ca_);
    tmp170 = IteratorStepValue_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp144}, TNode<JSAny>{tmp145}}, TNode<Map>{tmp43}, &label171, &label172, &tmp173, &tmp174);
    ca_.Goto(&block132, phi_bb128_8, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_13, phi_bb128_19, phi_bb128_20, phi_bb128_25, phi_bb128_26);
    if (label171.is_used()) {
      ca_.Bind(&label171);
      ca_.Goto(&block133, phi_bb128_8, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_13, phi_bb128_19, phi_bb128_20, phi_bb128_25, phi_bb128_26);
    }
    if (label172.is_used()) {
      ca_.Bind(&label172);
      ca_.Goto(&block134, phi_bb128_8, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_13, phi_bb128_19, phi_bb128_20, phi_bb128_25, phi_bb128_26);
    }
  }

  TNode<Uint32T> phi_bb129_8;
  TNode<JSAny> phi_bb129_10;
  TNode<FixedArray> phi_bb129_11;
  TNode<IntPtrT> phi_bb129_12;
  TNode<IntPtrT> phi_bb129_13;
  TNode<BoolT> phi_bb129_19;
  TNode<IntPtrT> phi_bb129_20;
  TNode<IntPtrT> phi_bb129_25;
  TNode<IntPtrT> phi_bb129_26;
  TNode<IntPtrT> phi_bb129_30;
  TNode<IntPtrT> phi_bb129_31;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_8, &phi_bb129_10, &phi_bb129_11, &phi_bb129_12, &phi_bb129_13, &phi_bb129_19, &phi_bb129_20, &phi_bb129_25, &phi_bb129_26, &phi_bb129_30, &phi_bb129_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb133_8;
  TNode<JSAny> phi_bb133_10;
  TNode<FixedArray> phi_bb133_11;
  TNode<IntPtrT> phi_bb133_12;
  TNode<IntPtrT> phi_bb133_13;
  TNode<BoolT> phi_bb133_19;
  TNode<IntPtrT> phi_bb133_20;
  TNode<IntPtrT> phi_bb133_25;
  TNode<IntPtrT> phi_bb133_26;
  TNode<BoolT> tmp175;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_8, &phi_bb133_10, &phi_bb133_11, &phi_bb133_12, &phi_bb133_13, &phi_bb133_19, &phi_bb133_20, &phi_bb133_25, &phi_bb133_26);
    tmp175 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block120, phi_bb133_8, phi_bb133_10, phi_bb133_11, phi_bb133_12, phi_bb133_13, tmp175, phi_bb133_20);
  }

  TNode<Uint32T> phi_bb134_8;
  TNode<JSAny> phi_bb134_10;
  TNode<FixedArray> phi_bb134_11;
  TNode<IntPtrT> phi_bb134_12;
  TNode<IntPtrT> phi_bb134_13;
  TNode<BoolT> phi_bb134_19;
  TNode<IntPtrT> phi_bb134_20;
  TNode<IntPtrT> phi_bb134_25;
  TNode<IntPtrT> phi_bb134_26;
  TNode<IntPtrT> tmp176;
  TNode<BoolT> tmp177;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_8, &phi_bb134_10, &phi_bb134_11, &phi_bb134_12, &phi_bb134_13, &phi_bb134_19, &phi_bb134_20, &phi_bb134_25, &phi_bb134_26);
    tmp176 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp177 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb134_13}, TNode<IntPtrT>{tmp176});
    ca_.Branch(tmp177, &block136, std::vector<compiler::Node*>{phi_bb134_8, phi_bb134_10, phi_bb134_11, phi_bb134_12, phi_bb134_13, phi_bb134_19, phi_bb134_20, phi_bb134_13, phi_bb134_13}, &block137, std::vector<compiler::Node*>{phi_bb134_8, phi_bb134_10, phi_bb134_11, phi_bb134_12, phi_bb134_13, phi_bb134_19, phi_bb134_20, phi_bb134_13, phi_bb134_13});
  }

  TNode<Uint32T> phi_bb132_8;
  TNode<JSAny> phi_bb132_10;
  TNode<FixedArray> phi_bb132_11;
  TNode<IntPtrT> phi_bb132_12;
  TNode<IntPtrT> phi_bb132_13;
  TNode<BoolT> phi_bb132_19;
  TNode<IntPtrT> phi_bb132_20;
  TNode<IntPtrT> phi_bb132_25;
  TNode<IntPtrT> phi_bb132_26;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_8, &phi_bb132_10, &phi_bb132_11, &phi_bb132_12, &phi_bb132_13, &phi_bb132_19, &phi_bb132_20, &phi_bb132_25, &phi_bb132_26);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp168, tmp169}, tmp170);
    ca_.Goto(&block120, phi_bb132_8, phi_bb132_10, phi_bb132_11, phi_bb132_12, phi_bb132_13, phi_bb132_19, phi_bb132_20);
  }

  TNode<Uint32T> phi_bb137_8;
  TNode<JSAny> phi_bb137_10;
  TNode<FixedArray> phi_bb137_11;
  TNode<IntPtrT> phi_bb137_12;
  TNode<IntPtrT> phi_bb137_13;
  TNode<BoolT> phi_bb137_19;
  TNode<IntPtrT> phi_bb137_20;
  TNode<IntPtrT> phi_bb137_23;
  TNode<IntPtrT> phi_bb137_24;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_8, &phi_bb137_10, &phi_bb137_11, &phi_bb137_12, &phi_bb137_13, &phi_bb137_19, &phi_bb137_20, &phi_bb137_23, &phi_bb137_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb136_8;
  TNode<JSAny> phi_bb136_10;
  TNode<FixedArray> phi_bb136_11;
  TNode<IntPtrT> phi_bb136_12;
  TNode<IntPtrT> phi_bb136_13;
  TNode<BoolT> phi_bb136_19;
  TNode<IntPtrT> phi_bb136_20;
  TNode<IntPtrT> phi_bb136_23;
  TNode<IntPtrT> phi_bb136_24;
  TNode<IntPtrT> tmp178;
  TNode<BoolT> tmp179;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_8, &phi_bb136_10, &phi_bb136_11, &phi_bb136_12, &phi_bb136_13, &phi_bb136_19, &phi_bb136_20, &phi_bb136_23, &phi_bb136_24);
    tmp178 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp179 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb136_24}, TNode<IntPtrT>{tmp178});
    ca_.Branch(tmp179, &block138, std::vector<compiler::Node*>{phi_bb136_8, phi_bb136_10, phi_bb136_11, phi_bb136_12, phi_bb136_13, phi_bb136_19, phi_bb136_20, phi_bb136_23, phi_bb136_24}, &block139, std::vector<compiler::Node*>{phi_bb136_8, phi_bb136_10, phi_bb136_11, phi_bb136_12, phi_bb136_13, phi_bb136_19, phi_bb136_20, phi_bb136_23, phi_bb136_24});
  }

  TNode<Uint32T> phi_bb139_8;
  TNode<JSAny> phi_bb139_10;
  TNode<FixedArray> phi_bb139_11;
  TNode<IntPtrT> phi_bb139_12;
  TNode<IntPtrT> phi_bb139_13;
  TNode<BoolT> phi_bb139_19;
  TNode<IntPtrT> phi_bb139_20;
  TNode<IntPtrT> phi_bb139_23;
  TNode<IntPtrT> phi_bb139_24;
  if (block139.is_used()) {
    ca_.Bind(&block139, &phi_bb139_8, &phi_bb139_10, &phi_bb139_11, &phi_bb139_12, &phi_bb139_13, &phi_bb139_19, &phi_bb139_20, &phi_bb139_23, &phi_bb139_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb138_8;
  TNode<JSAny> phi_bb138_10;
  TNode<FixedArray> phi_bb138_11;
  TNode<IntPtrT> phi_bb138_12;
  TNode<IntPtrT> phi_bb138_13;
  TNode<BoolT> phi_bb138_19;
  TNode<IntPtrT> phi_bb138_20;
  TNode<IntPtrT> phi_bb138_23;
  TNode<IntPtrT> phi_bb138_24;
  TNode<BoolT> tmp180;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_8, &phi_bb138_10, &phi_bb138_11, &phi_bb138_12, &phi_bb138_13, &phi_bb138_19, &phi_bb138_20, &phi_bb138_23, &phi_bb138_24);
    tmp180 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb138_24}, TNode<IntPtrT>{phi_bb138_13});
    ca_.Branch(tmp180, &block140, std::vector<compiler::Node*>{phi_bb138_8, phi_bb138_10, phi_bb138_11, phi_bb138_12, phi_bb138_13, phi_bb138_19, phi_bb138_20, phi_bb138_23, phi_bb138_24}, &block141, std::vector<compiler::Node*>{phi_bb138_8, phi_bb138_10, phi_bb138_11, phi_bb138_12, phi_bb138_13, phi_bb138_19, phi_bb138_20, phi_bb138_23, phi_bb138_24});
  }

  TNode<Uint32T> phi_bb141_8;
  TNode<JSAny> phi_bb141_10;
  TNode<FixedArray> phi_bb141_11;
  TNode<IntPtrT> phi_bb141_12;
  TNode<IntPtrT> phi_bb141_13;
  TNode<BoolT> phi_bb141_19;
  TNode<IntPtrT> phi_bb141_20;
  TNode<IntPtrT> phi_bb141_23;
  TNode<IntPtrT> phi_bb141_24;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_8, &phi_bb141_10, &phi_bb141_11, &phi_bb141_12, &phi_bb141_13, &phi_bb141_19, &phi_bb141_20, &phi_bb141_23, &phi_bb141_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb140_8;
  TNode<JSAny> phi_bb140_10;
  TNode<FixedArray> phi_bb140_11;
  TNode<IntPtrT> phi_bb140_12;
  TNode<IntPtrT> phi_bb140_13;
  TNode<BoolT> phi_bb140_19;
  TNode<IntPtrT> phi_bb140_20;
  TNode<IntPtrT> phi_bb140_23;
  TNode<IntPtrT> phi_bb140_24;
  TNode<IntPtrT> tmp181;
  TNode<TheHole> tmp182;
  TNode<FixedArray> tmp183;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_8, &phi_bb140_10, &phi_bb140_11, &phi_bb140_12, &phi_bb140_13, &phi_bb140_19, &phi_bb140_20, &phi_bb140_23, &phi_bb140_24);
    tmp181 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp182 = TheHole_0(state_);
    tmp183 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb140_11}, TNode<IntPtrT>{tmp181}, TNode<IntPtrT>{phi_bb140_13}, TNode<IntPtrT>{phi_bb140_24}, TNode<Hole>{tmp182});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp183}, false);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp173.value(), tmp174.value());
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb120_8;
  TNode<JSAny> phi_bb120_10;
  TNode<FixedArray> phi_bb120_11;
  TNode<IntPtrT> phi_bb120_12;
  TNode<IntPtrT> phi_bb120_13;
  TNode<BoolT> phi_bb120_19;
  TNode<IntPtrT> phi_bb120_20;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_8, &phi_bb120_10, &phi_bb120_11, &phi_bb120_12, &phi_bb120_13, &phi_bb120_19, &phi_bb120_20);
    ca_.Goto(&block119, phi_bb120_8, phi_bb120_10, phi_bb120_11, phi_bb120_12, phi_bb120_13, phi_bb120_19, phi_bb120_20);
  }

  TNode<Uint32T> phi_bb119_8;
  TNode<JSAny> phi_bb119_10;
  TNode<FixedArray> phi_bb119_11;
  TNode<IntPtrT> phi_bb119_12;
  TNode<IntPtrT> phi_bb119_13;
  TNode<BoolT> phi_bb119_19;
  TNode<IntPtrT> phi_bb119_20;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_8, &phi_bb119_10, &phi_bb119_11, &phi_bb119_12, &phi_bb119_13, &phi_bb119_19, &phi_bb119_20);
    tmp184 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp185 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb119_20}, TNode<IntPtrT>{tmp184});
    ca_.Goto(&block116, phi_bb119_8, phi_bb119_10, phi_bb119_11, phi_bb119_12, phi_bb119_13, phi_bb119_19, tmp185);
  }

  TNode<Uint32T> phi_bb115_8;
  TNode<JSAny> phi_bb115_10;
  TNode<FixedArray> phi_bb115_11;
  TNode<IntPtrT> phi_bb115_12;
  TNode<IntPtrT> phi_bb115_13;
  TNode<BoolT> phi_bb115_19;
  TNode<IntPtrT> phi_bb115_20;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_8, &phi_bb115_10, &phi_bb115_11, &phi_bb115_12, &phi_bb115_13, &phi_bb115_19, &phi_bb115_20);
    ca_.Branch(phi_bb115_19, &block142, std::vector<compiler::Node*>{phi_bb115_8, phi_bb115_10, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_19}, &block143, std::vector<compiler::Node*>{phi_bb115_8, phi_bb115_10, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_19});
  }

  TNode<Uint32T> phi_bb142_8;
  TNode<JSAny> phi_bb142_10;
  TNode<FixedArray> phi_bb142_11;
  TNode<IntPtrT> phi_bb142_12;
  TNode<IntPtrT> phi_bb142_13;
  TNode<BoolT> phi_bb142_19;
      TNode<JSAny> tmp187;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_8, &phi_bb142_10, &phi_bb142_11, &phi_bb142_12, &phi_bb142_13, &phi_bb142_19);
    compiler::CodeAssemblerExceptionHandlerLabel catch186__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch186__label);
    IteratorClose_0(state_, TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp144}, TNode<JSAny>{tmp145}});
    }
    if (catch186__label.is_used()) {
      compiler::CodeAssemblerLabel catch186_skip(&ca_);
      ca_.Goto(&catch186_skip);
      ca_.Bind(&catch186__label, &tmp187);
      ca_.Goto(&block146, phi_bb142_8, phi_bb142_10, phi_bb142_11, phi_bb142_12, phi_bb142_13, phi_bb142_19);
      ca_.Bind(&catch186_skip);
    }
    ca_.Goto(&block143, phi_bb142_8, phi_bb142_10, phi_bb142_11, phi_bb142_12, phi_bb142_13, phi_bb142_19);
  }

  TNode<Uint32T> phi_bb146_8;
  TNode<JSAny> phi_bb146_10;
  TNode<FixedArray> phi_bb146_11;
  TNode<IntPtrT> phi_bb146_12;
  TNode<IntPtrT> phi_bb146_13;
  TNode<BoolT> phi_bb146_19;
  TNode<Union<JSMessageObject, TheHole>> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<BoolT> tmp190;
  if (block146.is_used()) {
    ca_.Bind(&block146, &phi_bb146_8, &phi_bb146_10, &phi_bb146_11, &phi_bb146_12, &phi_bb146_13, &phi_bb146_19);
    tmp188 = GetAndResetPendingMessage_0(state_);
    tmp189 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp190 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb146_13}, TNode<IntPtrT>{tmp189});
    ca_.Branch(tmp190, &block148, std::vector<compiler::Node*>{phi_bb146_8, phi_bb146_10, phi_bb146_11, phi_bb146_12, phi_bb146_13, phi_bb146_19, phi_bb146_13, phi_bb146_13}, &block149, std::vector<compiler::Node*>{phi_bb146_8, phi_bb146_10, phi_bb146_11, phi_bb146_12, phi_bb146_13, phi_bb146_19, phi_bb146_13, phi_bb146_13});
  }

  TNode<Uint32T> phi_bb149_8;
  TNode<JSAny> phi_bb149_10;
  TNode<FixedArray> phi_bb149_11;
  TNode<IntPtrT> phi_bb149_12;
  TNode<IntPtrT> phi_bb149_13;
  TNode<BoolT> phi_bb149_19;
  TNode<IntPtrT> phi_bb149_22;
  TNode<IntPtrT> phi_bb149_23;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_8, &phi_bb149_10, &phi_bb149_11, &phi_bb149_12, &phi_bb149_13, &phi_bb149_19, &phi_bb149_22, &phi_bb149_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb148_8;
  TNode<JSAny> phi_bb148_10;
  TNode<FixedArray> phi_bb148_11;
  TNode<IntPtrT> phi_bb148_12;
  TNode<IntPtrT> phi_bb148_13;
  TNode<BoolT> phi_bb148_19;
  TNode<IntPtrT> phi_bb148_22;
  TNode<IntPtrT> phi_bb148_23;
  TNode<IntPtrT> tmp191;
  TNode<BoolT> tmp192;
  if (block148.is_used()) {
    ca_.Bind(&block148, &phi_bb148_8, &phi_bb148_10, &phi_bb148_11, &phi_bb148_12, &phi_bb148_13, &phi_bb148_19, &phi_bb148_22, &phi_bb148_23);
    tmp191 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp192 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb148_23}, TNode<IntPtrT>{tmp191});
    ca_.Branch(tmp192, &block150, std::vector<compiler::Node*>{phi_bb148_8, phi_bb148_10, phi_bb148_11, phi_bb148_12, phi_bb148_13, phi_bb148_19, phi_bb148_22, phi_bb148_23}, &block151, std::vector<compiler::Node*>{phi_bb148_8, phi_bb148_10, phi_bb148_11, phi_bb148_12, phi_bb148_13, phi_bb148_19, phi_bb148_22, phi_bb148_23});
  }

  TNode<Uint32T> phi_bb151_8;
  TNode<JSAny> phi_bb151_10;
  TNode<FixedArray> phi_bb151_11;
  TNode<IntPtrT> phi_bb151_12;
  TNode<IntPtrT> phi_bb151_13;
  TNode<BoolT> phi_bb151_19;
  TNode<IntPtrT> phi_bb151_22;
  TNode<IntPtrT> phi_bb151_23;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_8, &phi_bb151_10, &phi_bb151_11, &phi_bb151_12, &phi_bb151_13, &phi_bb151_19, &phi_bb151_22, &phi_bb151_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb150_8;
  TNode<JSAny> phi_bb150_10;
  TNode<FixedArray> phi_bb150_11;
  TNode<IntPtrT> phi_bb150_12;
  TNode<IntPtrT> phi_bb150_13;
  TNode<BoolT> phi_bb150_19;
  TNode<IntPtrT> phi_bb150_22;
  TNode<IntPtrT> phi_bb150_23;
  TNode<BoolT> tmp193;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_8, &phi_bb150_10, &phi_bb150_11, &phi_bb150_12, &phi_bb150_13, &phi_bb150_19, &phi_bb150_22, &phi_bb150_23);
    tmp193 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb150_23}, TNode<IntPtrT>{phi_bb150_13});
    ca_.Branch(tmp193, &block152, std::vector<compiler::Node*>{phi_bb150_8, phi_bb150_10, phi_bb150_11, phi_bb150_12, phi_bb150_13, phi_bb150_19, phi_bb150_22, phi_bb150_23}, &block153, std::vector<compiler::Node*>{phi_bb150_8, phi_bb150_10, phi_bb150_11, phi_bb150_12, phi_bb150_13, phi_bb150_19, phi_bb150_22, phi_bb150_23});
  }

  TNode<Uint32T> phi_bb153_8;
  TNode<JSAny> phi_bb153_10;
  TNode<FixedArray> phi_bb153_11;
  TNode<IntPtrT> phi_bb153_12;
  TNode<IntPtrT> phi_bb153_13;
  TNode<BoolT> phi_bb153_19;
  TNode<IntPtrT> phi_bb153_22;
  TNode<IntPtrT> phi_bb153_23;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_8, &phi_bb153_10, &phi_bb153_11, &phi_bb153_12, &phi_bb153_13, &phi_bb153_19, &phi_bb153_22, &phi_bb153_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb152_8;
  TNode<JSAny> phi_bb152_10;
  TNode<FixedArray> phi_bb152_11;
  TNode<IntPtrT> phi_bb152_12;
  TNode<IntPtrT> phi_bb152_13;
  TNode<BoolT> phi_bb152_19;
  TNode<IntPtrT> phi_bb152_22;
  TNode<IntPtrT> phi_bb152_23;
  TNode<IntPtrT> tmp194;
  TNode<TheHole> tmp195;
  TNode<FixedArray> tmp196;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_8, &phi_bb152_10, &phi_bb152_11, &phi_bb152_12, &phi_bb152_13, &phi_bb152_19, &phi_bb152_22, &phi_bb152_23);
    tmp194 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp195 = TheHole_0(state_);
    tmp196 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb152_11}, TNode<IntPtrT>{tmp194}, TNode<IntPtrT>{phi_bb152_13}, TNode<IntPtrT>{phi_bb152_23}, TNode<Hole>{tmp195});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp196}, false);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp187, tmp188);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb143_8;
  TNode<JSAny> phi_bb143_10;
  TNode<FixedArray> phi_bb143_11;
  TNode<IntPtrT> phi_bb143_12;
  TNode<IntPtrT> phi_bb143_13;
  TNode<BoolT> phi_bb143_19;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_8, &phi_bb143_10, &phi_bb143_11, &phi_bb143_12, &phi_bb143_13, &phi_bb143_19);
    ca_.Goto(&block103, phi_bb143_8, phi_bb143_10, phi_bb143_11, phi_bb143_12, phi_bb143_13);
  }

  TNode<Uint32T> phi_bb103_8;
  TNode<JSAny> phi_bb103_10;
  TNode<FixedArray> phi_bb103_11;
  TNode<IntPtrT> phi_bb103_12;
  TNode<IntPtrT> phi_bb103_13;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_8, &phi_bb103_10, &phi_bb103_11, &phi_bb103_12, &phi_bb103_13);
    ca_.Goto(&block101, phi_bb103_8, phi_bb103_10, phi_bb103_11, phi_bb103_12, phi_bb103_13, tmp141);
  }

  TNode<Uint32T> phi_bb101_8;
  TNode<JSAny> phi_bb101_10;
  TNode<FixedArray> phi_bb101_11;
  TNode<IntPtrT> phi_bb101_12;
  TNode<IntPtrT> phi_bb101_13;
  TNode<FixedArray> phi_bb101_14;
  TNode<IntPtrT> tmp197;
  TNode<BoolT> tmp198;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_8, &phi_bb101_10, &phi_bb101_11, &phi_bb101_12, &phi_bb101_13, &phi_bb101_14);
    tmp197 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp198 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb101_13}, TNode<IntPtrT>{tmp197});
    ca_.Branch(tmp198, &block155, std::vector<compiler::Node*>{phi_bb101_8, phi_bb101_10, phi_bb101_11, phi_bb101_12, phi_bb101_13, phi_bb101_14, phi_bb101_13, phi_bb101_13}, &block156, std::vector<compiler::Node*>{phi_bb101_8, phi_bb101_10, phi_bb101_11, phi_bb101_12, phi_bb101_13, phi_bb101_14, phi_bb101_13, phi_bb101_13});
  }

  TNode<Uint32T> phi_bb156_8;
  TNode<JSAny> phi_bb156_10;
  TNode<FixedArray> phi_bb156_11;
  TNode<IntPtrT> phi_bb156_12;
  TNode<IntPtrT> phi_bb156_13;
  TNode<FixedArray> phi_bb156_14;
  TNode<IntPtrT> phi_bb156_17;
  TNode<IntPtrT> phi_bb156_18;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_8, &phi_bb156_10, &phi_bb156_11, &phi_bb156_12, &phi_bb156_13, &phi_bb156_14, &phi_bb156_17, &phi_bb156_18);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb155_8;
  TNode<JSAny> phi_bb155_10;
  TNode<FixedArray> phi_bb155_11;
  TNode<IntPtrT> phi_bb155_12;
  TNode<IntPtrT> phi_bb155_13;
  TNode<FixedArray> phi_bb155_14;
  TNode<IntPtrT> phi_bb155_17;
  TNode<IntPtrT> phi_bb155_18;
  TNode<IntPtrT> tmp199;
  TNode<BoolT> tmp200;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_8, &phi_bb155_10, &phi_bb155_11, &phi_bb155_12, &phi_bb155_13, &phi_bb155_14, &phi_bb155_17, &phi_bb155_18);
    tmp199 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp200 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb155_18}, TNode<IntPtrT>{tmp199});
    ca_.Branch(tmp200, &block157, std::vector<compiler::Node*>{phi_bb155_8, phi_bb155_10, phi_bb155_11, phi_bb155_12, phi_bb155_13, phi_bb155_14, phi_bb155_17, phi_bb155_18}, &block158, std::vector<compiler::Node*>{phi_bb155_8, phi_bb155_10, phi_bb155_11, phi_bb155_12, phi_bb155_13, phi_bb155_14, phi_bb155_17, phi_bb155_18});
  }

  TNode<Uint32T> phi_bb158_8;
  TNode<JSAny> phi_bb158_10;
  TNode<FixedArray> phi_bb158_11;
  TNode<IntPtrT> phi_bb158_12;
  TNode<IntPtrT> phi_bb158_13;
  TNode<FixedArray> phi_bb158_14;
  TNode<IntPtrT> phi_bb158_17;
  TNode<IntPtrT> phi_bb158_18;
  if (block158.is_used()) {
    ca_.Bind(&block158, &phi_bb158_8, &phi_bb158_10, &phi_bb158_11, &phi_bb158_12, &phi_bb158_13, &phi_bb158_14, &phi_bb158_17, &phi_bb158_18);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb157_8;
  TNode<JSAny> phi_bb157_10;
  TNode<FixedArray> phi_bb157_11;
  TNode<IntPtrT> phi_bb157_12;
  TNode<IntPtrT> phi_bb157_13;
  TNode<FixedArray> phi_bb157_14;
  TNode<IntPtrT> phi_bb157_17;
  TNode<IntPtrT> phi_bb157_18;
  TNode<BoolT> tmp201;
  if (block157.is_used()) {
    ca_.Bind(&block157, &phi_bb157_8, &phi_bb157_10, &phi_bb157_11, &phi_bb157_12, &phi_bb157_13, &phi_bb157_14, &phi_bb157_17, &phi_bb157_18);
    tmp201 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb157_18}, TNode<IntPtrT>{phi_bb157_13});
    ca_.Branch(tmp201, &block159, std::vector<compiler::Node*>{phi_bb157_8, phi_bb157_10, phi_bb157_11, phi_bb157_12, phi_bb157_13, phi_bb157_14, phi_bb157_17, phi_bb157_18}, &block160, std::vector<compiler::Node*>{phi_bb157_8, phi_bb157_10, phi_bb157_11, phi_bb157_12, phi_bb157_13, phi_bb157_14, phi_bb157_17, phi_bb157_18});
  }

  TNode<Uint32T> phi_bb160_8;
  TNode<JSAny> phi_bb160_10;
  TNode<FixedArray> phi_bb160_11;
  TNode<IntPtrT> phi_bb160_12;
  TNode<IntPtrT> phi_bb160_13;
  TNode<FixedArray> phi_bb160_14;
  TNode<IntPtrT> phi_bb160_17;
  TNode<IntPtrT> phi_bb160_18;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_8, &phi_bb160_10, &phi_bb160_11, &phi_bb160_12, &phi_bb160_13, &phi_bb160_14, &phi_bb160_17, &phi_bb160_18);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb159_8;
  TNode<JSAny> phi_bb159_10;
  TNode<FixedArray> phi_bb159_11;
  TNode<IntPtrT> phi_bb159_12;
  TNode<IntPtrT> phi_bb159_13;
  TNode<FixedArray> phi_bb159_14;
  TNode<IntPtrT> phi_bb159_17;
  TNode<IntPtrT> phi_bb159_18;
  TNode<IntPtrT> tmp202;
  TNode<TheHole> tmp203;
  TNode<FixedArray> tmp204;
  TNode<JSIteratorZipHelper> tmp205;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_8, &phi_bb159_10, &phi_bb159_11, &phi_bb159_12, &phi_bb159_13, &phi_bb159_14, &phi_bb159_17, &phi_bb159_18);
    tmp202 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp203 = TheHole_0(state_);
    tmp204 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb159_11}, TNode<IntPtrT>{tmp202}, TNode<IntPtrT>{phi_bb159_13}, TNode<IntPtrT>{phi_bb159_18}, TNode<Hole>{tmp203});
    tmp205 = NewJSIteratorZipHelper_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp204}, TNode<FixedArray>{phi_bb159_14}, TNode<Uint32T>{phi_bb159_8});
    arguments.PopAndReturn(tmp205);
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1686&c=1
TNode<FixedArray> IteratorZipHelperNextCommon_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSIteratorZipHelper> p_helper, const char* p_methodName, compiler::CodeAssemblerLabel* label_Done, compiler::CodeAssemblerLabel* label_DoneWithException, compiler::TypedCodeAssemblerVariable<JSAny>* label_DoneWithException_parameter_0, compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>>* label_DoneWithException_parameter_1) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block20(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block36(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block37(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block38(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block58(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block61(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block73(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block78(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block86(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block87(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block88(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block89(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block98(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block99(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block100(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block101(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block110(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block111(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block112(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block113(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block116(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block117(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block119(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block120(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block123(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block124(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block128(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block129(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block130(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block131(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block132(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block133(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block138(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block141(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block142(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block143(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block148(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block154(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block157(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block156(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block160(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block161(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block162(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block163(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block164(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block170(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block175(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block174(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block173(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block182(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block181(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block180(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block183(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block184(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block185(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block179(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block186(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block187(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT> block188(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block193(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block194(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block197(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block198(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block199(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block200(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block205(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block206(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT> block209(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block210(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block211(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block122(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block214(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block215(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block213(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block212(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block218(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block219(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block220(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block221(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block217(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block224(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block225(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block230(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block231(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block236(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block235(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block234(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, JSAny> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, JSAny> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block237(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block242(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block243(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT> block246(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block247(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block248(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_helper, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp3}, TNode<Uint32T>{tmp4});
    ca_.Branch(tmp5, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp6;
  TNode<FixedArray> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Smi> tmp12;
  TNode<Uint32T> tmp13;
  TNode<Map> tmp14;
  TNode<FixedArray> tmp15;
      TNode<JSAny> tmp17;
  TNode<IntPtrT> tmp18;
      TNode<JSAny> tmp20;
  TNode<Smi> tmp21;
  TNode<IntPtrT> tmp22;
      TNode<JSAny> tmp24;
  TNode<IntPtrT> tmp25;
      TNode<JSAny> tmp27;
  TNode<BoolT> tmp28;
      TNode<JSAny> tmp30;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp7 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_helper, tmp6});
    tmp8 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp10 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp9});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp12 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp11});
    tmp13 = SmiUntag_JSIteratorZipHelperMode_0(state_, TNode<Smi>{tmp12});
    MarkIteratorHelperAsExecuting_0(state_, TNode<JSIteratorHelper>{p_helper});
    tmp14 = GetIteratorResultMap_0(state_, TNode<Context>{p_context});
    compiler::CodeAssemblerExceptionHandlerLabel catch16__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch16__label);
    tmp15 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp10});
    }
    if (catch16__label.is_used()) {
      compiler::CodeAssemblerLabel catch16_skip(&ca_);
      ca_.Goto(&catch16_skip);
      ca_.Bind(&catch16__label, &tmp17);
      ca_.Goto(&block8);
      ca_.Bind(&catch16_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch19__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch19__label);
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch19__label.is_used()) {
      compiler::CodeAssemblerLabel catch19_skip(&ca_);
      ca_.Goto(&catch19_skip);
      ca_.Bind(&catch19__label, &tmp20);
      ca_.Goto(&block11);
      ca_.Bind(&catch19_skip);
    }
    tmp21 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp18});
    compiler::CodeAssemblerExceptionHandlerLabel catch23__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch23__label);
    tmp22 = CodeStubAssembler(state_).SmiUntag(TNode<Smi>{tmp21});
    }
    if (catch23__label.is_used()) {
      compiler::CodeAssemblerLabel catch23_skip(&ca_);
      ca_.Goto(&catch23_skip);
      ca_.Bind(&catch23__label, &tmp24);
      ca_.Goto(&block12);
      ca_.Bind(&catch23_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch26__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch26__label);
    tmp25 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    }
    if (catch26__label.is_used()) {
      compiler::CodeAssemblerLabel catch26_skip(&ca_);
      ca_.Goto(&catch26_skip);
      ca_.Bind(&catch26__label, &tmp27);
      ca_.Goto(&block13);
      ca_.Bind(&catch26_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch29__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch29__label);
    tmp28 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp25});
    }
    if (catch29__label.is_used()) {
      compiler::CodeAssemblerLabel catch29_skip(&ca_);
      ca_.Goto(&catch29_skip);
      ca_.Bind(&catch29__label, &tmp30);
      ca_.Goto(&block14);
      ca_.Bind(&catch29_skip);
    }
    ca_.Branch(tmp28, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp31;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp31 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp17, tmp31);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp32;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp32 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp20, tmp32);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp33;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp33 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp24, tmp33);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp34;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp34 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp27, tmp34);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp35;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp35 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp30, tmp35);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1707});
      CodeStubAssembler(state_).FailAssert("Torque assert 'SmiUntag(helper.active_count) > 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp36;
      TNode<JSAny> tmp38;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerExceptionHandlerLabel catch37__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch37__label);
    tmp36 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    }
    if (catch37__label.is_used()) {
      compiler::CodeAssemblerLabel catch37_skip(&ca_);
      ca_.Goto(&catch37_skip);
      ca_.Bind(&catch37__label, &tmp38);
      ca_.Goto(&block15);
      ca_.Bind(&catch37_skip);
    }
    ca_.Goto(&block18, tmp36);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp39;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp39 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp38, tmp39);
  }

  TNode<IntPtrT> phi_bb18_6;
  TNode<BoolT> tmp40;
      TNode<JSAny> tmp42;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch41__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch41__label);
    tmp40 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb18_6}, TNode<IntPtrT>{tmp10});
    }
    if (catch41__label.is_used()) {
      compiler::CodeAssemblerLabel catch41_skip(&ca_);
      ca_.Goto(&catch41_skip);
      ca_.Bind(&catch41__label, &tmp42);
      ca_.Goto(&block20, phi_bb18_6, phi_bb18_6);
      ca_.Bind(&catch41_skip);
    }
    ca_.Branch(tmp40, &block16, std::vector<compiler::Node*>{phi_bb18_6}, &block17, std::vector<compiler::Node*>{phi_bb18_6});
  }

  TNode<IntPtrT> phi_bb20_6;
  TNode<IntPtrT> phi_bb20_7;
  TNode<Union<JSMessageObject, TheHole>> tmp43;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_6, &phi_bb20_7);
    tmp43 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp42, tmp43);
  }

  TNode<IntPtrT> phi_bb16_6;
  TNode<Undefined> tmp44;
  TNode<IntPtrT> tmp45;
      TNode<JSAny> tmp47;
  TNode<FixedArray> tmp48;
  TNode<Union<HeapObject, TaggedIndex>> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
      TNode<JSAny> tmp53;
  TNode<IntPtrT> tmp54;
      TNode<JSAny> tmp56;
  TNode<IntPtrT> tmp57;
      TNode<JSAny> tmp59;
  TNode<UintPtrT> tmp60;
  TNode<UintPtrT> tmp61;
  TNode<BoolT> tmp62;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_6);
    tmp44 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch46__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch46__label);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    }
    if (catch46__label.is_used()) {
      compiler::CodeAssemblerLabel catch46_skip(&ca_);
      ca_.Goto(&catch46_skip);
      ca_.Bind(&catch46__label, &tmp47);
      ca_.Goto(&block21, phi_bb16_6);
      ca_.Bind(&catch46_skip);
    }
    tmp48 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_helper, tmp45});
    compiler::CodeAssemblerExceptionHandlerLabel catch52__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch52__label);
    std::tie(tmp49, tmp50, tmp51) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch52__label.is_used()) {
      compiler::CodeAssemblerLabel catch52_skip(&ca_);
      ca_.Goto(&catch52_skip);
      ca_.Bind(&catch52__label, &tmp53);
      ca_.Goto(&block22, phi_bb16_6);
      ca_.Bind(&catch52_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch55__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch55__label);
    tmp54 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch55__label.is_used()) {
      compiler::CodeAssemblerLabel catch55_skip(&ca_);
      ca_.Goto(&catch55_skip);
      ca_.Bind(&catch55__label, &tmp56);
      ca_.Goto(&block23, phi_bb16_6, phi_bb16_6);
      ca_.Bind(&catch55_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch58__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch58__label);
    tmp57 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp54}, TNode<IntPtrT>{phi_bb16_6});
    }
    if (catch58__label.is_used()) {
      compiler::CodeAssemblerLabel catch58_skip(&ca_);
      ca_.Goto(&catch58_skip);
      ca_.Bind(&catch58__label, &tmp59);
      ca_.Goto(&block24, phi_bb16_6, phi_bb16_6);
      ca_.Bind(&catch58_skip);
    }
    tmp60 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp57});
    tmp61 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp51});
    tmp62 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp60}, TNode<UintPtrT>{tmp61});
    ca_.Branch(tmp62, &block29, std::vector<compiler::Node*>{phi_bb16_6}, &block30, std::vector<compiler::Node*>{phi_bb16_6});
  }

  TNode<IntPtrT> phi_bb21_6;
  TNode<Union<JSMessageObject, TheHole>> tmp63;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_6);
    tmp63 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp47, tmp63);
  }

  TNode<IntPtrT> phi_bb22_6;
  TNode<Union<JSMessageObject, TheHole>> tmp64;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_6);
    tmp64 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp53, tmp64);
  }

  TNode<IntPtrT> phi_bb23_6;
  TNode<IntPtrT> phi_bb23_13;
  TNode<Union<JSMessageObject, TheHole>> tmp65;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_6, &phi_bb23_13);
    tmp65 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp56, tmp65);
  }

  TNode<IntPtrT> phi_bb24_6;
  TNode<IntPtrT> phi_bb24_13;
  TNode<Union<JSMessageObject, TheHole>> tmp66;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_6, &phi_bb24_13);
    tmp66 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp59, tmp66);
  }

  TNode<IntPtrT> phi_bb29_6;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<Union<HeapObject, TaggedIndex>> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<Object> tmp71;
  TNode<Union<HeapObject, TaggedIndex>> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<IntPtrT> tmp74;
      TNode<JSAny> tmp76;
  TNode<IntPtrT> tmp77;
      TNode<JSAny> tmp79;
  TNode<IntPtrT> tmp80;
      TNode<JSAny> tmp82;
  TNode<IntPtrT> tmp83;
      TNode<JSAny> tmp85;
  TNode<IntPtrT> tmp86;
      TNode<JSAny> tmp88;
  TNode<UintPtrT> tmp89;
  TNode<UintPtrT> tmp90;
  TNode<BoolT> tmp91;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_6);
    tmp67 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp57});
    tmp68 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp50}, TNode<IntPtrT>{tmp67});
    std::tie(tmp69, tmp70) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp49}, TNode<IntPtrT>{tmp68}).Flatten();
    tmp71 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp69, tmp70});
    compiler::CodeAssemblerExceptionHandlerLabel catch75__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch75__label);
    std::tie(tmp72, tmp73, tmp74) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch75__label.is_used()) {
      compiler::CodeAssemblerLabel catch75_skip(&ca_);
      ca_.Goto(&catch75_skip);
      ca_.Bind(&catch75__label, &tmp76);
      ca_.Goto(&block35, phi_bb29_6);
      ca_.Bind(&catch75_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch78__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch78__label);
    tmp77 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch78__label.is_used()) {
      compiler::CodeAssemblerLabel catch78_skip(&ca_);
      ca_.Goto(&catch78_skip);
      ca_.Bind(&catch78__label, &tmp79);
      ca_.Goto(&block36, phi_bb29_6, phi_bb29_6);
      ca_.Bind(&catch78_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch81__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch81__label);
    tmp80 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp77}, TNode<IntPtrT>{phi_bb29_6});
    }
    if (catch81__label.is_used()) {
      compiler::CodeAssemblerLabel catch81_skip(&ca_);
      ca_.Goto(&catch81_skip);
      ca_.Bind(&catch81__label, &tmp82);
      ca_.Goto(&block37, phi_bb29_6, phi_bb29_6);
      ca_.Bind(&catch81_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch84__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch84__label);
    tmp83 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch84__label.is_used()) {
      compiler::CodeAssemblerLabel catch84_skip(&ca_);
      ca_.Goto(&catch84_skip);
      ca_.Bind(&catch84__label, &tmp85);
      ca_.Goto(&block38, phi_bb29_6);
      ca_.Bind(&catch84_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch87__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch87__label);
    tmp86 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp80}, TNode<IntPtrT>{tmp83});
    }
    if (catch87__label.is_used()) {
      compiler::CodeAssemblerLabel catch87_skip(&ca_);
      ca_.Goto(&catch87_skip);
      ca_.Bind(&catch87__label, &tmp88);
      ca_.Goto(&block39, phi_bb29_6);
      ca_.Bind(&catch87_skip);
    }
    tmp89 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp86});
    tmp90 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp74});
    tmp91 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp89}, TNode<UintPtrT>{tmp90});
    ca_.Branch(tmp91, &block44, std::vector<compiler::Node*>{phi_bb29_6}, &block45, std::vector<compiler::Node*>{phi_bb29_6});
  }

  TNode<IntPtrT> phi_bb30_6;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb35_6;
  TNode<Union<JSMessageObject, TheHole>> tmp92;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6);
    tmp92 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp76, tmp92);
  }

  TNode<IntPtrT> phi_bb36_6;
  TNode<IntPtrT> phi_bb36_14;
  TNode<Union<JSMessageObject, TheHole>> tmp93;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_6, &phi_bb36_14);
    tmp93 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp79, tmp93);
  }

  TNode<IntPtrT> phi_bb37_6;
  TNode<IntPtrT> phi_bb37_14;
  TNode<Union<JSMessageObject, TheHole>> tmp94;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_6, &phi_bb37_14);
    tmp94 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp82, tmp94);
  }

  TNode<IntPtrT> phi_bb38_6;
  TNode<Union<JSMessageObject, TheHole>> tmp95;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6);
    tmp95 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp85, tmp95);
  }

  TNode<IntPtrT> phi_bb39_6;
  TNode<Union<JSMessageObject, TheHole>> tmp96;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6);
    tmp96 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp88, tmp96);
  }

  TNode<IntPtrT> phi_bb44_6;
  TNode<IntPtrT> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<Union<HeapObject, TaggedIndex>> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<Object> tmp101;
  TNode<JSAny> tmp102;
      TNode<JSAny> tmp105;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6);
    tmp97 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp86});
    tmp98 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp73}, TNode<IntPtrT>{tmp97});
    std::tie(tmp99, tmp100) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp72}, TNode<IntPtrT>{tmp98}).Flatten();
    tmp101 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp99, tmp100});
    compiler::CodeAssemblerLabel label103(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch104__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch104__label);
    tmp102 = Cast_JSAny_0(state_, TNode<Object>{tmp101}, &label103);
    }
    if (catch104__label.is_used()) {
      compiler::CodeAssemblerLabel catch104_skip(&ca_);
      ca_.Goto(&catch104_skip);
      ca_.Bind(&catch104__label, &tmp105);
      ca_.Goto(&block50, phi_bb44_6);
      ca_.Bind(&catch104_skip);
    }
    ca_.Goto(&block48, phi_bb44_6);
    if (label103.is_used()) {
      ca_.Bind(&label103);
      ca_.Goto(&block49, phi_bb44_6);
    }
  }

  TNode<IntPtrT> phi_bb45_6;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb50_6;
  TNode<Union<JSMessageObject, TheHole>> tmp106;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_6);
    tmp106 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp105, tmp106);
  }

  TNode<IntPtrT> phi_bb49_6;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1716:21");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb48_6;
  TNode<TheHole> tmp107;
  TNode<BoolT> tmp108;
      TNode<JSAny> tmp110;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_6);
    tmp107 = TheHole_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch109__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch109__label);
    tmp108 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp71}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp107});
    }
    if (catch109__label.is_used()) {
      compiler::CodeAssemblerLabel catch109_skip(&ca_);
      ca_.Goto(&catch109_skip);
      ca_.Bind(&catch109__label, &tmp110);
      ca_.Goto(&block53, phi_bb48_6);
      ca_.Bind(&catch109_skip);
    }
    ca_.Branch(tmp108, &block51, std::vector<compiler::Node*>{phi_bb48_6}, &block52, std::vector<compiler::Node*>{phi_bb48_6});
  }

  TNode<IntPtrT> phi_bb53_6;
  TNode<Union<JSMessageObject, TheHole>> tmp111;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_6);
    tmp111 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp110, tmp111);
  }

  TNode<IntPtrT> phi_bb51_6;
  TNode<Uint32T> tmp112;
      TNode<JSAny> tmp114;
  TNode<BoolT> tmp115;
      TNode<JSAny> tmp117;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch113__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch113__label);
    tmp112 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kLongest));
    }
    if (catch113__label.is_used()) {
      compiler::CodeAssemblerLabel catch113_skip(&ca_);
      ca_.Goto(&catch113_skip);
      ca_.Bind(&catch113__label, &tmp114);
      ca_.Goto(&block57, phi_bb51_6);
      ca_.Bind(&catch113_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch116__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch116__label);
    tmp115 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp13}, TNode<Uint32T>{tmp112});
    }
    if (catch116__label.is_used()) {
      compiler::CodeAssemblerLabel catch116_skip(&ca_);
      ca_.Goto(&catch116_skip);
      ca_.Bind(&catch116__label, &tmp117);
      ca_.Goto(&block58, phi_bb51_6);
      ca_.Bind(&catch116_skip);
    }
    ca_.Branch(tmp115, &block55, std::vector<compiler::Node*>{phi_bb51_6}, &block56, std::vector<compiler::Node*>{phi_bb51_6});
  }

  TNode<IntPtrT> phi_bb57_6;
  TNode<Union<JSMessageObject, TheHole>> tmp118;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_6);
    tmp118 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp114, tmp118);
  }

  TNode<IntPtrT> phi_bb58_6;
  TNode<Union<JSMessageObject, TheHole>> tmp119;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_6);
    tmp119 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp117, tmp119);
  }

  TNode<IntPtrT> phi_bb56_6;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1721});
      CodeStubAssembler(state_).FailAssert("Torque assert 'mode == JSIteratorZipHelperMode::kLongest' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb55_6;
  TNode<IntPtrT> tmp120;
      TNode<JSAny> tmp122;
  TNode<FixedArray> tmp123;
  TNode<Union<HeapObject, TaggedIndex>> tmp124;
  TNode<IntPtrT> tmp125;
  TNode<IntPtrT> tmp126;
      TNode<JSAny> tmp128;
  TNode<UintPtrT> tmp129;
  TNode<UintPtrT> tmp130;
  TNode<BoolT> tmp131;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch121__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch121__label);
    tmp120 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch121__label.is_used()) {
      compiler::CodeAssemblerLabel catch121_skip(&ca_);
      ca_.Goto(&catch121_skip);
      ca_.Bind(&catch121__label, &tmp122);
      ca_.Goto(&block61, phi_bb55_6);
      ca_.Bind(&catch121_skip);
    }
    tmp123 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_helper, tmp120});
    compiler::CodeAssemblerExceptionHandlerLabel catch127__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch127__label);
    std::tie(tmp124, tmp125, tmp126) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp123}).Flatten();
    }
    if (catch127__label.is_used()) {
      compiler::CodeAssemblerLabel catch127_skip(&ca_);
      ca_.Goto(&catch127_skip);
      ca_.Bind(&catch127__label, &tmp128);
      ca_.Goto(&block62, phi_bb55_6);
      ca_.Bind(&catch127_skip);
    }
    tmp129 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb55_6});
    tmp130 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp126});
    tmp131 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp129}, TNode<UintPtrT>{tmp130});
    ca_.Branch(tmp131, &block67, std::vector<compiler::Node*>{phi_bb55_6, phi_bb55_6, phi_bb55_6, phi_bb55_6, phi_bb55_6}, &block68, std::vector<compiler::Node*>{phi_bb55_6, phi_bb55_6, phi_bb55_6, phi_bb55_6, phi_bb55_6});
  }

  TNode<IntPtrT> phi_bb61_6;
  TNode<Union<JSMessageObject, TheHole>> tmp132;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_6);
    tmp132 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp122, tmp132);
  }

  TNode<IntPtrT> phi_bb62_6;
  TNode<Union<JSMessageObject, TheHole>> tmp133;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_6);
    tmp133 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp128, tmp133);
  }

  TNode<IntPtrT> phi_bb67_6;
  TNode<IntPtrT> phi_bb67_18;
  TNode<IntPtrT> phi_bb67_19;
  TNode<IntPtrT> phi_bb67_23;
  TNode<IntPtrT> phi_bb67_24;
  TNode<IntPtrT> tmp134;
  TNode<IntPtrT> tmp135;
  TNode<Union<HeapObject, TaggedIndex>> tmp136;
  TNode<IntPtrT> tmp137;
  TNode<Object> tmp138;
  TNode<JSAny> tmp139;
      TNode<JSAny> tmp142;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_18, &phi_bb67_19, &phi_bb67_23, &phi_bb67_24);
    tmp134 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb67_24});
    tmp135 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp125}, TNode<IntPtrT>{tmp134});
    std::tie(tmp136, tmp137) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp124}, TNode<IntPtrT>{tmp135}).Flatten();
    tmp138 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp136, tmp137});
    compiler::CodeAssemblerLabel label140(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch141__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch141__label);
    tmp139 = Cast_JSAny_0(state_, TNode<Object>{tmp138}, &label140);
    }
    if (catch141__label.is_used()) {
      compiler::CodeAssemblerLabel catch141_skip(&ca_);
      ca_.Goto(&catch141_skip);
      ca_.Bind(&catch141__label, &tmp142);
      ca_.Goto(&block73, phi_bb67_6);
      ca_.Bind(&catch141_skip);
    }
    ca_.Goto(&block71, phi_bb67_6);
    if (label140.is_used()) {
      ca_.Bind(&label140);
      ca_.Goto(&block72, phi_bb67_6);
    }
  }

  TNode<IntPtrT> phi_bb68_6;
  TNode<IntPtrT> phi_bb68_18;
  TNode<IntPtrT> phi_bb68_19;
  TNode<IntPtrT> phi_bb68_23;
  TNode<IntPtrT> phi_bb68_24;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_6, &phi_bb68_18, &phi_bb68_19, &phi_bb68_23, &phi_bb68_24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb73_6;
  TNode<Union<JSMessageObject, TheHole>> tmp143;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_6);
    tmp143 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp142, tmp143);
  }

  TNode<IntPtrT> phi_bb72_6;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1723:67");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb71_6;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_6);
    ca_.Goto(&block54, phi_bb71_6, tmp139);
  }

  TNode<IntPtrT> phi_bb52_6;
  TNode<JSReceiver> tmp144;
      TNode<JSAny> tmp147;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_6);
    compiler::CodeAssemblerLabel label145(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch146__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch146__label);
    tmp144 = Cast_JSReceiver_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp71}, &label145);
    }
    if (catch146__label.is_used()) {
      compiler::CodeAssemblerLabel catch146_skip(&ca_);
      ca_.Goto(&catch146_skip);
      ca_.Bind(&catch146__label, &tmp147);
      ca_.Goto(&block78, phi_bb52_6);
      ca_.Bind(&catch146_skip);
    }
    ca_.Goto(&block76, phi_bb52_6);
    if (label145.is_used()) {
      ca_.Bind(&label145);
      ca_.Goto(&block77, phi_bb52_6);
    }
  }

  TNode<IntPtrT> phi_bb78_6;
  TNode<Union<JSMessageObject, TheHole>> tmp148;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_6);
    tmp148 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp147, tmp148);
  }

  TNode<IntPtrT> phi_bb77_6;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1726:61");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb76_6;
  TNode<JSAny> tmp149;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp152(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp153(&ca_);
      TNode<JSAny> tmp155;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_6);
    compiler::CodeAssemblerLabel label150(&ca_);
    compiler::CodeAssemblerLabel label151(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch154__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch154__label);
    tmp149 = IteratorStepValue_0(state_, TNode<Context>{p_context}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp144}, TNode<JSAny>{tmp102}}, TNode<Map>{tmp14}, &label150, &label151, &tmp152, &tmp153);
    }
    if (catch154__label.is_used()) {
      compiler::CodeAssemblerLabel catch154_skip(&ca_);
      ca_.Goto(&catch154_skip);
      ca_.Bind(&catch154__label, &tmp155);
      ca_.Goto(&block86, phi_bb76_6);
      ca_.Bind(&catch154_skip);
    }
    ca_.Goto(&block83, phi_bb76_6);
    if (label150.is_used()) {
      ca_.Bind(&label150);
      ca_.Goto(&block84, phi_bb76_6);
    }
    if (label151.is_used()) {
      ca_.Bind(&label151);
      ca_.Goto(&block85, phi_bb76_6);
    }
  }

  TNode<IntPtrT> phi_bb86_6;
  TNode<Union<JSMessageObject, TheHole>> tmp156;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_6);
    tmp156 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp155, tmp156);
  }

  TNode<IntPtrT> phi_bb84_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<IntPtrT> tmp159;
      TNode<JSAny> tmp161;
  TNode<IntPtrT> tmp162;
      TNode<JSAny> tmp164;
  TNode<IntPtrT> tmp165;
      TNode<JSAny> tmp167;
  TNode<UintPtrT> tmp168;
  TNode<UintPtrT> tmp169;
  TNode<BoolT> tmp170;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch160__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch160__label);
    std::tie(tmp157, tmp158, tmp159) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch160__label.is_used()) {
      compiler::CodeAssemblerLabel catch160_skip(&ca_);
      ca_.Goto(&catch160_skip);
      ca_.Bind(&catch160__label, &tmp161);
      ca_.Goto(&block99, phi_bb84_6);
      ca_.Bind(&catch160_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch163__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch163__label);
    tmp162 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch163__label.is_used()) {
      compiler::CodeAssemblerLabel catch163_skip(&ca_);
      ca_.Goto(&catch163_skip);
      ca_.Bind(&catch163__label, &tmp164);
      ca_.Goto(&block100, phi_bb84_6, phi_bb84_6);
      ca_.Bind(&catch163_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch166__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch166__label);
    tmp165 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp162}, TNode<IntPtrT>{phi_bb84_6});
    }
    if (catch166__label.is_used()) {
      compiler::CodeAssemblerLabel catch166_skip(&ca_);
      ca_.Goto(&catch166_skip);
      ca_.Bind(&catch166__label, &tmp167);
      ca_.Goto(&block101, phi_bb84_6, phi_bb84_6);
      ca_.Bind(&catch166_skip);
    }
    tmp168 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp165});
    tmp169 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp159});
    tmp170 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp168}, TNode<UintPtrT>{tmp169});
    ca_.Branch(tmp170, &block106, std::vector<compiler::Node*>{phi_bb84_6}, &block107, std::vector<compiler::Node*>{phi_bb84_6});
  }

  TNode<IntPtrT> phi_bb85_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp171;
  TNode<IntPtrT> tmp172;
  TNode<IntPtrT> tmp173;
      TNode<JSAny> tmp175;
  TNode<IntPtrT> tmp176;
      TNode<JSAny> tmp178;
  TNode<IntPtrT> tmp179;
      TNode<JSAny> tmp181;
  TNode<UintPtrT> tmp182;
  TNode<UintPtrT> tmp183;
  TNode<BoolT> tmp184;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch174__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch174__label);
    std::tie(tmp171, tmp172, tmp173) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch174__label.is_used()) {
      compiler::CodeAssemblerLabel catch174_skip(&ca_);
      ca_.Goto(&catch174_skip);
      ca_.Bind(&catch174__label, &tmp175);
      ca_.Goto(&block87, phi_bb85_6);
      ca_.Bind(&catch174_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch177__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch177__label);
    tmp176 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch177__label.is_used()) {
      compiler::CodeAssemblerLabel catch177_skip(&ca_);
      ca_.Goto(&catch177_skip);
      ca_.Bind(&catch177__label, &tmp178);
      ca_.Goto(&block88, phi_bb85_6, phi_bb85_6);
      ca_.Bind(&catch177_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch180__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch180__label);
    tmp179 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp176}, TNode<IntPtrT>{phi_bb85_6});
    }
    if (catch180__label.is_used()) {
      compiler::CodeAssemblerLabel catch180_skip(&ca_);
      ca_.Goto(&catch180_skip);
      ca_.Bind(&catch180__label, &tmp181);
      ca_.Goto(&block89, phi_bb85_6, phi_bb85_6);
      ca_.Bind(&catch180_skip);
    }
    tmp182 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp179});
    tmp183 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp173});
    tmp184 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp182}, TNode<UintPtrT>{tmp183});
    ca_.Branch(tmp184, &block94, std::vector<compiler::Node*>{phi_bb85_6}, &block95, std::vector<compiler::Node*>{phi_bb85_6});
  }

  TNode<IntPtrT> phi_bb83_6;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_6);
    ca_.Goto(&block79, phi_bb83_6, tmp149);
  }

  TNode<IntPtrT> phi_bb87_6;
  TNode<Union<JSMessageObject, TheHole>> tmp185;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_6);
    tmp185 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp175, tmp185);
  }

  TNode<IntPtrT> phi_bb88_6;
  TNode<IntPtrT> phi_bb88_18;
  TNode<Union<JSMessageObject, TheHole>> tmp186;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_6, &phi_bb88_18);
    tmp186 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp178, tmp186);
  }

  TNode<IntPtrT> phi_bb89_6;
  TNode<IntPtrT> phi_bb89_18;
  TNode<Union<JSMessageObject, TheHole>> tmp187;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_6, &phi_bb89_18);
    tmp187 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp181, tmp187);
  }

  TNode<IntPtrT> phi_bb94_6;
  TNode<IntPtrT> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<Union<HeapObject, TaggedIndex>> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<TheHole> tmp192;
      TNode<JSAny> tmp194;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_6);
    tmp188 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp179});
    tmp189 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp172}, TNode<IntPtrT>{tmp188});
    std::tie(tmp190, tmp191) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp171}, TNode<IntPtrT>{tmp189}).Flatten();
    tmp192 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp190, tmp191}, tmp192);
    compiler::CodeAssemblerExceptionHandlerLabel catch193__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch193__label);
    IteratorZipCloseAll_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp48}, false);
    }
    if (catch193__label.is_used()) {
      compiler::CodeAssemblerLabel catch193_skip(&ca_);
      ca_.Goto(&catch193_skip);
      ca_.Bind(&catch193__label, &tmp194);
      ca_.Goto(&block98, phi_bb94_6);
      ca_.Bind(&catch193_skip);
    }
    ca_.Goto(&block2, tmp152.value(), tmp153.value());
  }

  TNode<IntPtrT> phi_bb95_6;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb98_6;
  TNode<Union<JSMessageObject, TheHole>> tmp195;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_6);
    tmp195 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp194, tmp195);
  }

  TNode<IntPtrT> phi_bb99_6;
  TNode<Union<JSMessageObject, TheHole>> tmp196;
  if (block99.is_used()) {
    ca_.Bind(&block99, &phi_bb99_6);
    tmp196 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp161, tmp196);
  }

  TNode<IntPtrT> phi_bb100_6;
  TNode<IntPtrT> phi_bb100_16;
  TNode<Union<JSMessageObject, TheHole>> tmp197;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_6, &phi_bb100_16);
    tmp197 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp164, tmp197);
  }

  TNode<IntPtrT> phi_bb101_6;
  TNode<IntPtrT> phi_bb101_16;
  TNode<Union<JSMessageObject, TheHole>> tmp198;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_6, &phi_bb101_16);
    tmp198 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp167, tmp198);
  }

  TNode<IntPtrT> phi_bb106_6;
  TNode<IntPtrT> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<Union<HeapObject, TaggedIndex>> tmp201;
  TNode<IntPtrT> tmp202;
  TNode<TheHole> tmp203;
  TNode<IntPtrT> tmp204;
      TNode<JSAny> tmp206;
  TNode<IntPtrT> tmp207;
      TNode<JSAny> tmp209;
  TNode<Smi> tmp210;
  TNode<Smi> tmp211;
      TNode<JSAny> tmp213;
  TNode<Smi> tmp214;
      TNode<JSAny> tmp216;
  TNode<Uint32T> tmp217;
      TNode<JSAny> tmp219;
  TNode<BoolT> tmp220;
      TNode<JSAny> tmp222;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_6);
    tmp199 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp165});
    tmp200 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp158}, TNode<IntPtrT>{tmp199});
    std::tie(tmp201, tmp202) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp157}, TNode<IntPtrT>{tmp200}).Flatten();
    tmp203 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp201, tmp202}, tmp203);
    compiler::CodeAssemblerExceptionHandlerLabel catch205__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch205__label);
    tmp204 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch205__label.is_used()) {
      compiler::CodeAssemblerLabel catch205_skip(&ca_);
      ca_.Goto(&catch205_skip);
      ca_.Bind(&catch205__label, &tmp206);
      ca_.Goto(&block110, phi_bb106_6);
      ca_.Bind(&catch205_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch208__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch208__label);
    tmp207 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch208__label.is_used()) {
      compiler::CodeAssemblerLabel catch208_skip(&ca_);
      ca_.Goto(&catch208_skip);
      ca_.Bind(&catch208__label, &tmp209);
      ca_.Goto(&block111, phi_bb106_6);
      ca_.Bind(&catch208_skip);
    }
    tmp210 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp207});
    compiler::CodeAssemblerExceptionHandlerLabel catch212__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch212__label);
    tmp211 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch212__label.is_used()) {
      compiler::CodeAssemblerLabel catch212_skip(&ca_);
      ca_.Goto(&catch212_skip);
      ca_.Bind(&catch212__label, &tmp213);
      ca_.Goto(&block112, phi_bb106_6);
      ca_.Bind(&catch212_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch215__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch215__label);
    tmp214 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp210}, TNode<Smi>{tmp211});
    }
    if (catch215__label.is_used()) {
      compiler::CodeAssemblerLabel catch215_skip(&ca_);
      ca_.Goto(&catch215_skip);
      ca_.Bind(&catch215__label, &tmp216);
      ca_.Goto(&block113, phi_bb106_6);
      ca_.Bind(&catch215_skip);
    }
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp204}, tmp214);
    compiler::CodeAssemblerExceptionHandlerLabel catch218__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch218__label);
    tmp217 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kShortest));
    }
    if (catch218__label.is_used()) {
      compiler::CodeAssemblerLabel catch218_skip(&ca_);
      ca_.Goto(&catch218_skip);
      ca_.Bind(&catch218__label, &tmp219);
      ca_.Goto(&block116, phi_bb106_6);
      ca_.Bind(&catch218_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch221__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch221__label);
    tmp220 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp13}, TNode<Uint32T>{tmp217});
    }
    if (catch221__label.is_used()) {
      compiler::CodeAssemblerLabel catch221_skip(&ca_);
      ca_.Goto(&catch221_skip);
      ca_.Bind(&catch221__label, &tmp222);
      ca_.Goto(&block117, phi_bb106_6);
      ca_.Bind(&catch221_skip);
    }
    ca_.Branch(tmp220, &block114, std::vector<compiler::Node*>{phi_bb106_6}, &block115, std::vector<compiler::Node*>{phi_bb106_6});
  }

  TNode<IntPtrT> phi_bb107_6;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb110_6;
  TNode<Union<JSMessageObject, TheHole>> tmp223;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_6);
    tmp223 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp206, tmp223);
  }

  TNode<IntPtrT> phi_bb111_6;
  TNode<Union<JSMessageObject, TheHole>> tmp224;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_6);
    tmp224 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp209, tmp224);
  }

  TNode<IntPtrT> phi_bb112_6;
  TNode<Union<JSMessageObject, TheHole>> tmp225;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_6);
    tmp225 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp213, tmp225);
  }

  TNode<IntPtrT> phi_bb113_6;
  TNode<Union<JSMessageObject, TheHole>> tmp226;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_6);
    tmp226 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp216, tmp226);
  }

  TNode<IntPtrT> phi_bb116_6;
  TNode<Union<JSMessageObject, TheHole>> tmp227;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_6);
    tmp227 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp219, tmp227);
  }

  TNode<IntPtrT> phi_bb117_6;
  TNode<Union<JSMessageObject, TheHole>> tmp228;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_6);
    tmp228 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp222, tmp228);
  }

  TNode<IntPtrT> phi_bb114_6;
      TNode<JSAny> tmp230;
      TNode<JSAny> tmp232;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch229__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch229__label);
    IteratorZipCloseAll_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp48}, true);
    }
    if (catch229__label.is_used()) {
      compiler::CodeAssemblerLabel catch229_skip(&ca_);
      ca_.Goto(&catch229_skip);
      ca_.Bind(&catch229__label, &tmp230);
      ca_.Goto(&block119, phi_bb114_6);
      ca_.Bind(&catch229_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch231__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch231__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    }
    if (catch231__label.is_used()) {
      compiler::CodeAssemblerLabel catch231_skip(&ca_);
      ca_.Goto(&catch231_skip);
      ca_.Bind(&catch231__label, &tmp232);
      ca_.Goto(&block120, phi_bb114_6);
      ca_.Bind(&catch231_skip);
    }
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> phi_bb119_6;
  TNode<Union<JSMessageObject, TheHole>> tmp233;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_6);
    tmp233 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp230, tmp233);
  }

  TNode<IntPtrT> phi_bb120_6;
  TNode<Union<JSMessageObject, TheHole>> tmp234;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_6);
    tmp234 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp232, tmp234);
  }

  TNode<IntPtrT> phi_bb115_6;
  TNode<Uint32T> tmp235;
      TNode<JSAny> tmp237;
  TNode<BoolT> tmp238;
      TNode<JSAny> tmp240;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch236__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch236__label);
    tmp235 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kStrict));
    }
    if (catch236__label.is_used()) {
      compiler::CodeAssemblerLabel catch236_skip(&ca_);
      ca_.Goto(&catch236_skip);
      ca_.Bind(&catch236__label, &tmp237);
      ca_.Goto(&block123, phi_bb115_6);
      ca_.Bind(&catch236_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch239__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch239__label);
    tmp238 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp13}, TNode<Uint32T>{tmp235});
    }
    if (catch239__label.is_used()) {
      compiler::CodeAssemblerLabel catch239_skip(&ca_);
      ca_.Goto(&catch239_skip);
      ca_.Bind(&catch239__label, &tmp240);
      ca_.Goto(&block124, phi_bb115_6);
      ca_.Bind(&catch239_skip);
    }
    ca_.Branch(tmp238, &block121, std::vector<compiler::Node*>{phi_bb115_6}, &block122, std::vector<compiler::Node*>{phi_bb115_6});
  }

  TNode<IntPtrT> phi_bb123_6;
  TNode<Union<JSMessageObject, TheHole>> tmp241;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_6);
    tmp241 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp237, tmp241);
  }

  TNode<IntPtrT> phi_bb124_6;
  TNode<Union<JSMessageObject, TheHole>> tmp242;
  if (block124.is_used()) {
    ca_.Bind(&block124, &phi_bb124_6);
    tmp242 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp240, tmp242);
  }

  TNode<IntPtrT> phi_bb121_6;
  TNode<IntPtrT> tmp243;
      TNode<JSAny> tmp245;
  TNode<BoolT> tmp246;
      TNode<JSAny> tmp248;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch244__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch244__label);
    tmp243 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    }
    if (catch244__label.is_used()) {
      compiler::CodeAssemblerLabel catch244_skip(&ca_);
      ca_.Goto(&catch244_skip);
      ca_.Bind(&catch244__label, &tmp245);
      ca_.Goto(&block128, phi_bb121_6, phi_bb121_6, phi_bb121_6);
      ca_.Bind(&catch244_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch247__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch247__label);
    tmp246 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb121_6}, TNode<IntPtrT>{tmp243});
    }
    if (catch247__label.is_used()) {
      compiler::CodeAssemblerLabel catch247_skip(&ca_);
      ca_.Goto(&catch247_skip);
      ca_.Bind(&catch247__label, &tmp248);
      ca_.Goto(&block129, phi_bb121_6, phi_bb121_6);
      ca_.Bind(&catch247_skip);
    }
    ca_.Branch(tmp246, &block126, std::vector<compiler::Node*>{phi_bb121_6}, &block127, std::vector<compiler::Node*>{phi_bb121_6});
  }

  TNode<IntPtrT> phi_bb128_6;
  TNode<IntPtrT> phi_bb128_12;
  TNode<IntPtrT> phi_bb128_13;
  TNode<Union<JSMessageObject, TheHole>> tmp249;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_6, &phi_bb128_12, &phi_bb128_13);
    tmp249 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp245, tmp249);
  }

  TNode<IntPtrT> phi_bb129_6;
  TNode<IntPtrT> phi_bb129_12;
  TNode<Union<JSMessageObject, TheHole>> tmp250;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_6, &phi_bb129_12);
    tmp250 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp248, tmp250);
  }

  TNode<IntPtrT> phi_bb126_6;
      TNode<JSAny> tmp252;
      TNode<JSAny> tmp254;
      TNode<JSAny> tmp256;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch251__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch251__label);
    IteratorZipCloseAll_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp48}, false);
    }
    if (catch251__label.is_used()) {
      compiler::CodeAssemblerLabel catch251_skip(&ca_);
      ca_.Goto(&catch251_skip);
      ca_.Bind(&catch251__label, &tmp252);
      ca_.Goto(&block130, phi_bb126_6);
      ca_.Bind(&catch251_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch253__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch253__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    }
    if (catch253__label.is_used()) {
      compiler::CodeAssemblerLabel catch253_skip(&ca_);
      ca_.Goto(&catch253_skip);
      ca_.Bind(&catch253__label, &tmp254);
      ca_.Goto(&block131, phi_bb126_6);
      ca_.Bind(&catch253_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch255__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch255__label);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIteratorZipStrictMismatch), p_methodName);
    }
    if (catch255__label.is_used()) {
      compiler::CodeAssemblerLabel catch255_skip(&ca_);
      ca_.Bind(&catch255__label, &tmp256);
      ca_.Goto(&block132, phi_bb126_6);
    }
  }

  TNode<IntPtrT> phi_bb130_6;
  TNode<Union<JSMessageObject, TheHole>> tmp257;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_6);
    tmp257 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp252, tmp257);
  }

  TNode<IntPtrT> phi_bb131_6;
  TNode<Union<JSMessageObject, TheHole>> tmp258;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_6);
    tmp258 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp254, tmp258);
  }

  TNode<IntPtrT> phi_bb132_6;
  TNode<Union<JSMessageObject, TheHole>> tmp259;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_6);
    tmp259 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp256, tmp259);
  }

  TNode<IntPtrT> phi_bb127_6;
  TNode<IntPtrT> tmp260;
      TNode<JSAny> tmp262;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch261__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch261__label);
    tmp260 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch261__label.is_used()) {
      compiler::CodeAssemblerLabel catch261_skip(&ca_);
      ca_.Goto(&catch261_skip);
      ca_.Bind(&catch261__label, &tmp262);
      ca_.Goto(&block133, phi_bb127_6);
      ca_.Bind(&catch261_skip);
    }
    ca_.Goto(&block136, phi_bb127_6, tmp260);
  }

  TNode<IntPtrT> phi_bb133_6;
  TNode<Union<JSMessageObject, TheHole>> tmp263;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_6);
    tmp263 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp262, tmp263);
  }

  TNode<IntPtrT> phi_bb136_6;
  TNode<IntPtrT> phi_bb136_12;
  TNode<BoolT> tmp264;
      TNode<JSAny> tmp266;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_6, &phi_bb136_12);
    compiler::CodeAssemblerExceptionHandlerLabel catch265__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch265__label);
    tmp264 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb136_12}, TNode<IntPtrT>{tmp10});
    }
    if (catch265__label.is_used()) {
      compiler::CodeAssemblerLabel catch265_skip(&ca_);
      ca_.Goto(&catch265_skip);
      ca_.Bind(&catch265__label, &tmp266);
      ca_.Goto(&block138, phi_bb136_6, phi_bb136_12, phi_bb136_12);
      ca_.Bind(&catch265_skip);
    }
    ca_.Branch(tmp264, &block134, std::vector<compiler::Node*>{phi_bb136_6, phi_bb136_12}, &block135, std::vector<compiler::Node*>{phi_bb136_6, phi_bb136_12});
  }

  TNode<IntPtrT> phi_bb138_6;
  TNode<IntPtrT> phi_bb138_12;
  TNode<IntPtrT> phi_bb138_13;
  TNode<Union<JSMessageObject, TheHole>> tmp267;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_6, &phi_bb138_12, &phi_bb138_13);
    tmp267 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp266, tmp267);
  }

  TNode<IntPtrT> phi_bb134_6;
  TNode<IntPtrT> phi_bb134_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<IntPtrT> tmp270;
      TNode<JSAny> tmp272;
  TNode<IntPtrT> tmp273;
      TNode<JSAny> tmp275;
  TNode<IntPtrT> tmp276;
      TNode<JSAny> tmp278;
  TNode<UintPtrT> tmp279;
  TNode<UintPtrT> tmp280;
  TNode<BoolT> tmp281;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_6, &phi_bb134_12);
    compiler::CodeAssemblerExceptionHandlerLabel catch271__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch271__label);
    std::tie(tmp268, tmp269, tmp270) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch271__label.is_used()) {
      compiler::CodeAssemblerLabel catch271_skip(&ca_);
      ca_.Goto(&catch271_skip);
      ca_.Bind(&catch271__label, &tmp272);
      ca_.Goto(&block141, phi_bb134_6, phi_bb134_12);
      ca_.Bind(&catch271_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch274__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch274__label);
    tmp273 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch274__label.is_used()) {
      compiler::CodeAssemblerLabel catch274_skip(&ca_);
      ca_.Goto(&catch274_skip);
      ca_.Bind(&catch274__label, &tmp275);
      ca_.Goto(&block142, phi_bb134_6, phi_bb134_12, phi_bb134_12);
      ca_.Bind(&catch274_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch277__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch277__label);
    tmp276 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp273}, TNode<IntPtrT>{phi_bb134_12});
    }
    if (catch277__label.is_used()) {
      compiler::CodeAssemblerLabel catch277_skip(&ca_);
      ca_.Goto(&catch277_skip);
      ca_.Bind(&catch277__label, &tmp278);
      ca_.Goto(&block143, phi_bb134_6, phi_bb134_12, phi_bb134_12);
      ca_.Bind(&catch277_skip);
    }
    tmp279 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp276});
    tmp280 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp270});
    tmp281 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp279}, TNode<UintPtrT>{tmp280});
    ca_.Branch(tmp281, &block148, std::vector<compiler::Node*>{phi_bb134_6, phi_bb134_12}, &block149, std::vector<compiler::Node*>{phi_bb134_6, phi_bb134_12});
  }

  TNode<IntPtrT> phi_bb141_6;
  TNode<IntPtrT> phi_bb141_12;
  TNode<Union<JSMessageObject, TheHole>> tmp282;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_6, &phi_bb141_12);
    tmp282 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp272, tmp282);
  }

  TNode<IntPtrT> phi_bb142_6;
  TNode<IntPtrT> phi_bb142_12;
  TNode<IntPtrT> phi_bb142_17;
  TNode<Union<JSMessageObject, TheHole>> tmp283;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_6, &phi_bb142_12, &phi_bb142_17);
    tmp283 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp275, tmp283);
  }

  TNode<IntPtrT> phi_bb143_6;
  TNode<IntPtrT> phi_bb143_12;
  TNode<IntPtrT> phi_bb143_17;
  TNode<Union<JSMessageObject, TheHole>> tmp284;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_6, &phi_bb143_12, &phi_bb143_17);
    tmp284 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp278, tmp284);
  }

  TNode<IntPtrT> phi_bb148_6;
  TNode<IntPtrT> phi_bb148_12;
  TNode<IntPtrT> tmp285;
  TNode<IntPtrT> tmp286;
  TNode<Union<HeapObject, TaggedIndex>> tmp287;
  TNode<IntPtrT> tmp288;
  TNode<Object> tmp289;
  TNode<JSReceiver> tmp290;
      TNode<JSAny> tmp293;
  if (block148.is_used()) {
    ca_.Bind(&block148, &phi_bb148_6, &phi_bb148_12);
    tmp285 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp276});
    tmp286 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp269}, TNode<IntPtrT>{tmp285});
    std::tie(tmp287, tmp288) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp268}, TNode<IntPtrT>{tmp286}).Flatten();
    tmp289 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp287, tmp288});
    compiler::CodeAssemblerLabel label291(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch292__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch292__label);
    tmp290 = Cast_JSReceiver_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp289}, &label291);
    }
    if (catch292__label.is_used()) {
      compiler::CodeAssemblerLabel catch292_skip(&ca_);
      ca_.Goto(&catch292_skip);
      ca_.Bind(&catch292__label, &tmp293);
      ca_.Goto(&block154, phi_bb148_6, phi_bb148_12);
      ca_.Bind(&catch292_skip);
    }
    ca_.Goto(&block152, phi_bb148_6, phi_bb148_12);
    if (label291.is_used()) {
      ca_.Bind(&label291);
      ca_.Goto(&block153, phi_bb148_6, phi_bb148_12);
    }
  }

  TNode<IntPtrT> phi_bb149_6;
  TNode<IntPtrT> phi_bb149_12;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_6, &phi_bb149_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb154_6;
  TNode<IntPtrT> phi_bb154_12;
  TNode<Union<JSMessageObject, TheHole>> tmp294;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_6, &phi_bb154_12);
    tmp294 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp293, tmp294);
  }

  TNode<IntPtrT> phi_bb153_6;
  TNode<IntPtrT> phi_bb153_12;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_6, &phi_bb153_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1771:29");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb152_6;
  TNode<IntPtrT> phi_bb152_12;
  TNode<TheHole> tmp295;
  TNode<BoolT> tmp296;
      TNode<JSAny> tmp298;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_6, &phi_bb152_12);
    tmp295 = TheHole_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch297__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch297__label);
    tmp296 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp290}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp295});
    }
    if (catch297__label.is_used()) {
      compiler::CodeAssemblerLabel catch297_skip(&ca_);
      ca_.Goto(&catch297_skip);
      ca_.Bind(&catch297__label, &tmp298);
      ca_.Goto(&block157, phi_bb152_6, phi_bb152_12);
      ca_.Bind(&catch297_skip);
    }
    ca_.Branch(tmp296, &block155, std::vector<compiler::Node*>{phi_bb152_6, phi_bb152_12}, &block156, std::vector<compiler::Node*>{phi_bb152_6, phi_bb152_12});
  }

  TNode<IntPtrT> phi_bb157_6;
  TNode<IntPtrT> phi_bb157_12;
  TNode<Union<JSMessageObject, TheHole>> tmp299;
  if (block157.is_used()) {
    ca_.Bind(&block157, &phi_bb157_6, &phi_bb157_12);
    tmp299 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp298, tmp299);
  }

  TNode<IntPtrT> phi_bb156_6;
  TNode<IntPtrT> phi_bb156_12;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_6, &phi_bb156_12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1773});
      CodeStubAssembler(state_).FailAssert("Torque assert 'innerIterObject != TheHole' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb155_6;
  TNode<IntPtrT> phi_bb155_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp300;
  TNode<IntPtrT> tmp301;
  TNode<IntPtrT> tmp302;
      TNode<JSAny> tmp304;
  TNode<IntPtrT> tmp305;
      TNode<JSAny> tmp307;
  TNode<IntPtrT> tmp308;
      TNode<JSAny> tmp310;
  TNode<IntPtrT> tmp311;
      TNode<JSAny> tmp313;
  TNode<IntPtrT> tmp314;
      TNode<JSAny> tmp316;
  TNode<UintPtrT> tmp317;
  TNode<UintPtrT> tmp318;
  TNode<BoolT> tmp319;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_6, &phi_bb155_12);
    compiler::CodeAssemblerExceptionHandlerLabel catch303__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch303__label);
    std::tie(tmp300, tmp301, tmp302) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch303__label.is_used()) {
      compiler::CodeAssemblerLabel catch303_skip(&ca_);
      ca_.Goto(&catch303_skip);
      ca_.Bind(&catch303__label, &tmp304);
      ca_.Goto(&block160, phi_bb155_6, phi_bb155_12);
      ca_.Bind(&catch303_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch306__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch306__label);
    tmp305 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch306__label.is_used()) {
      compiler::CodeAssemblerLabel catch306_skip(&ca_);
      ca_.Goto(&catch306_skip);
      ca_.Bind(&catch306__label, &tmp307);
      ca_.Goto(&block161, phi_bb155_6, phi_bb155_12, phi_bb155_12);
      ca_.Bind(&catch306_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch309__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch309__label);
    tmp308 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp305}, TNode<IntPtrT>{phi_bb155_12});
    }
    if (catch309__label.is_used()) {
      compiler::CodeAssemblerLabel catch309_skip(&ca_);
      ca_.Goto(&catch309_skip);
      ca_.Bind(&catch309__label, &tmp310);
      ca_.Goto(&block162, phi_bb155_6, phi_bb155_12, phi_bb155_12);
      ca_.Bind(&catch309_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch312__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch312__label);
    tmp311 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    }
    if (catch312__label.is_used()) {
      compiler::CodeAssemblerLabel catch312_skip(&ca_);
      ca_.Goto(&catch312_skip);
      ca_.Bind(&catch312__label, &tmp313);
      ca_.Goto(&block163, phi_bb155_6, phi_bb155_12);
      ca_.Bind(&catch312_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch315__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch315__label);
    tmp314 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp308}, TNode<IntPtrT>{tmp311});
    }
    if (catch315__label.is_used()) {
      compiler::CodeAssemblerLabel catch315_skip(&ca_);
      ca_.Goto(&catch315_skip);
      ca_.Bind(&catch315__label, &tmp316);
      ca_.Goto(&block164, phi_bb155_6, phi_bb155_12);
      ca_.Bind(&catch315_skip);
    }
    tmp317 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp314});
    tmp318 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp302});
    tmp319 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp317}, TNode<UintPtrT>{tmp318});
    ca_.Branch(tmp319, &block169, std::vector<compiler::Node*>{phi_bb155_6, phi_bb155_12}, &block170, std::vector<compiler::Node*>{phi_bb155_6, phi_bb155_12});
  }

  TNode<IntPtrT> phi_bb160_6;
  TNode<IntPtrT> phi_bb160_12;
  TNode<Union<JSMessageObject, TheHole>> tmp320;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_6, &phi_bb160_12);
    tmp320 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp304, tmp320);
  }

  TNode<IntPtrT> phi_bb161_6;
  TNode<IntPtrT> phi_bb161_12;
  TNode<IntPtrT> phi_bb161_18;
  TNode<Union<JSMessageObject, TheHole>> tmp321;
  if (block161.is_used()) {
    ca_.Bind(&block161, &phi_bb161_6, &phi_bb161_12, &phi_bb161_18);
    tmp321 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp307, tmp321);
  }

  TNode<IntPtrT> phi_bb162_6;
  TNode<IntPtrT> phi_bb162_12;
  TNode<IntPtrT> phi_bb162_18;
  TNode<Union<JSMessageObject, TheHole>> tmp322;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_6, &phi_bb162_12, &phi_bb162_18);
    tmp322 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp310, tmp322);
  }

  TNode<IntPtrT> phi_bb163_6;
  TNode<IntPtrT> phi_bb163_12;
  TNode<Union<JSMessageObject, TheHole>> tmp323;
  if (block163.is_used()) {
    ca_.Bind(&block163, &phi_bb163_6, &phi_bb163_12);
    tmp323 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp313, tmp323);
  }

  TNode<IntPtrT> phi_bb164_6;
  TNode<IntPtrT> phi_bb164_12;
  TNode<Union<JSMessageObject, TheHole>> tmp324;
  if (block164.is_used()) {
    ca_.Bind(&block164, &phi_bb164_6, &phi_bb164_12);
    tmp324 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp316, tmp324);
  }

  TNode<IntPtrT> phi_bb169_6;
  TNode<IntPtrT> phi_bb169_12;
  TNode<IntPtrT> tmp325;
  TNode<IntPtrT> tmp326;
  TNode<Union<HeapObject, TaggedIndex>> tmp327;
  TNode<IntPtrT> tmp328;
  TNode<Object> tmp329;
  TNode<JSAny> tmp330;
      TNode<JSAny> tmp333;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_6, &phi_bb169_12);
    tmp325 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp314});
    tmp326 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp301}, TNode<IntPtrT>{tmp325});
    std::tie(tmp327, tmp328) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp300}, TNode<IntPtrT>{tmp326}).Flatten();
    tmp329 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp327, tmp328});
    compiler::CodeAssemblerLabel label331(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch332__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch332__label);
    tmp330 = Cast_JSAny_0(state_, TNode<Object>{tmp329}, &label331);
    }
    if (catch332__label.is_used()) {
      compiler::CodeAssemblerLabel catch332_skip(&ca_);
      ca_.Goto(&catch332_skip);
      ca_.Bind(&catch332__label, &tmp333);
      ca_.Goto(&block175, phi_bb169_6, phi_bb169_12);
      ca_.Bind(&catch332_skip);
    }
    ca_.Goto(&block173, phi_bb169_6, phi_bb169_12);
    if (label331.is_used()) {
      ca_.Bind(&label331);
      ca_.Goto(&block174, phi_bb169_6, phi_bb169_12);
    }
  }

  TNode<IntPtrT> phi_bb170_6;
  TNode<IntPtrT> phi_bb170_12;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_6, &phi_bb170_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb175_6;
  TNode<IntPtrT> phi_bb175_12;
  TNode<Union<JSMessageObject, TheHole>> tmp334;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_6, &phi_bb175_12);
    tmp334 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp333, tmp334);
  }

  TNode<IntPtrT> phi_bb174_6;
  TNode<IntPtrT> phi_bb174_12;
  if (block174.is_used()) {
    ca_.Bind(&block174, &phi_bb174_6, &phi_bb174_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1776:29");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb173_6;
  TNode<IntPtrT> phi_bb173_12;
  TNode<JSReceiver> tmp335;
      TNode<JSAny> tmp338;
  if (block173.is_used()) {
    ca_.Bind(&block173, &phi_bb173_6, &phi_bb173_12);
    compiler::CodeAssemblerLabel label336(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch337__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch337__label);
    tmp335 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{p_context}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp290}, TNode<JSAny>{tmp330}}, TNode<Map>{tmp14}, &label336);
    }
    if (catch337__label.is_used()) {
      compiler::CodeAssemblerLabel catch337_skip(&ca_);
      ca_.Goto(&catch337_skip);
      ca_.Bind(&catch337__label, &tmp338);
      ca_.Goto(&block182, phi_bb173_6, phi_bb173_12);
      ca_.Bind(&catch337_skip);
    }
    ca_.Goto(&block180, phi_bb173_6, phi_bb173_12);
    if (label336.is_used()) {
      ca_.Bind(&label336);
      ca_.Goto(&block181, phi_bb173_6, phi_bb173_12);
    }
  }

  TNode<IntPtrT> phi_bb182_6;
  TNode<IntPtrT> phi_bb182_12;
  TNode<Union<JSMessageObject, TheHole>> tmp339;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_6, &phi_bb182_12);
    tmp339 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block179, phi_bb182_6, phi_bb182_12, tmp338, tmp339);
  }

  TNode<IntPtrT> phi_bb181_6;
  TNode<IntPtrT> phi_bb181_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp340;
  TNode<IntPtrT> tmp341;
  TNode<IntPtrT> tmp342;
      TNode<JSAny> tmp344;
  TNode<IntPtrT> tmp345;
      TNode<JSAny> tmp347;
  TNode<IntPtrT> tmp348;
      TNode<JSAny> tmp350;
  TNode<UintPtrT> tmp351;
  TNode<UintPtrT> tmp352;
  TNode<BoolT> tmp353;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_6, &phi_bb181_12);
    compiler::CodeAssemblerExceptionHandlerLabel catch343__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch343__label);
    std::tie(tmp340, tmp341, tmp342) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch343__label.is_used()) {
      compiler::CodeAssemblerLabel catch343_skip(&ca_);
      ca_.Goto(&catch343_skip);
      ca_.Bind(&catch343__label, &tmp344);
      ca_.Goto(&block198, phi_bb181_6, phi_bb181_12);
      ca_.Bind(&catch343_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch346__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch346__label);
    tmp345 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch346__label.is_used()) {
      compiler::CodeAssemblerLabel catch346_skip(&ca_);
      ca_.Goto(&catch346_skip);
      ca_.Bind(&catch346__label, &tmp347);
      ca_.Goto(&block199, phi_bb181_6, phi_bb181_12, phi_bb181_12);
      ca_.Bind(&catch346_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch349__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch349__label);
    tmp348 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp345}, TNode<IntPtrT>{phi_bb181_12});
    }
    if (catch349__label.is_used()) {
      compiler::CodeAssemblerLabel catch349_skip(&ca_);
      ca_.Goto(&catch349_skip);
      ca_.Bind(&catch349__label, &tmp350);
      ca_.Goto(&block200, phi_bb181_6, phi_bb181_12, phi_bb181_12);
      ca_.Bind(&catch349_skip);
    }
    tmp351 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp348});
    tmp352 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp342});
    tmp353 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp351}, TNode<UintPtrT>{tmp352});
    ca_.Branch(tmp353, &block205, std::vector<compiler::Node*>{phi_bb181_6, phi_bb181_12}, &block206, std::vector<compiler::Node*>{phi_bb181_6, phi_bb181_12});
  }

  TNode<IntPtrT> phi_bb180_6;
  TNode<IntPtrT> phi_bb180_12;
      TNode<JSAny> tmp355;
      TNode<JSAny> tmp357;
      TNode<JSAny> tmp359;
  if (block180.is_used()) {
    ca_.Bind(&block180, &phi_bb180_6, &phi_bb180_12);
    compiler::CodeAssemblerExceptionHandlerLabel catch354__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch354__label);
    IteratorZipCloseAll_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp48}, false);
    }
    if (catch354__label.is_used()) {
      compiler::CodeAssemblerLabel catch354_skip(&ca_);
      ca_.Goto(&catch354_skip);
      ca_.Bind(&catch354__label, &tmp355);
      ca_.Goto(&block183, phi_bb180_6, phi_bb180_12);
      ca_.Bind(&catch354_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch356__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch356__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    }
    if (catch356__label.is_used()) {
      compiler::CodeAssemblerLabel catch356_skip(&ca_);
      ca_.Goto(&catch356_skip);
      ca_.Bind(&catch356__label, &tmp357);
      ca_.Goto(&block184, phi_bb180_6, phi_bb180_12);
      ca_.Bind(&catch356_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch358__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch358__label);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIteratorZipStrictMismatch), p_methodName);
    }
    if (catch358__label.is_used()) {
      compiler::CodeAssemblerLabel catch358_skip(&ca_);
      ca_.Bind(&catch358__label, &tmp359);
      ca_.Goto(&block185, phi_bb180_6, phi_bb180_12);
    }
  }

  TNode<IntPtrT> phi_bb183_6;
  TNode<IntPtrT> phi_bb183_12;
  TNode<Union<JSMessageObject, TheHole>> tmp360;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_6, &phi_bb183_12);
    tmp360 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block179, phi_bb183_6, phi_bb183_12, tmp355, tmp360);
  }

  TNode<IntPtrT> phi_bb184_6;
  TNode<IntPtrT> phi_bb184_12;
  TNode<Union<JSMessageObject, TheHole>> tmp361;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_6, &phi_bb184_12);
    tmp361 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block179, phi_bb184_6, phi_bb184_12, tmp357, tmp361);
  }

  TNode<IntPtrT> phi_bb185_6;
  TNode<IntPtrT> phi_bb185_12;
  TNode<Union<JSMessageObject, TheHole>> tmp362;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_6, &phi_bb185_12);
    tmp362 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block179, phi_bb185_6, phi_bb185_12, tmp359, tmp362);
  }

  TNode<IntPtrT> phi_bb179_6;
  TNode<IntPtrT> phi_bb179_12;
  TNode<JSAny> phi_bb179_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb179_16;
  TNode<Union<HeapObject, TaggedIndex>> tmp363;
  TNode<IntPtrT> tmp364;
  TNode<IntPtrT> tmp365;
      TNode<JSAny> tmp367;
  TNode<IntPtrT> tmp368;
      TNode<JSAny> tmp370;
  TNode<IntPtrT> tmp371;
      TNode<JSAny> tmp373;
  TNode<UintPtrT> tmp374;
  TNode<UintPtrT> tmp375;
  TNode<BoolT> tmp376;
  if (block179.is_used()) {
    ca_.Bind(&block179, &phi_bb179_6, &phi_bb179_12, &phi_bb179_15, &phi_bb179_16);
    compiler::CodeAssemblerExceptionHandlerLabel catch366__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch366__label);
    std::tie(tmp363, tmp364, tmp365) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp48}).Flatten();
    }
    if (catch366__label.is_used()) {
      compiler::CodeAssemblerLabel catch366_skip(&ca_);
      ca_.Goto(&catch366_skip);
      ca_.Bind(&catch366__label, &tmp367);
      ca_.Goto(&block186, phi_bb179_6, phi_bb179_12, phi_bb179_15, phi_bb179_16);
      ca_.Bind(&catch366_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch369__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch369__label);
    tmp368 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    }
    if (catch369__label.is_used()) {
      compiler::CodeAssemblerLabel catch369_skip(&ca_);
      ca_.Goto(&catch369_skip);
      ca_.Bind(&catch369__label, &tmp370);
      ca_.Goto(&block187, phi_bb179_6, phi_bb179_12, phi_bb179_15, phi_bb179_16, phi_bb179_12);
      ca_.Bind(&catch369_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch372__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch372__label);
    tmp371 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp368}, TNode<IntPtrT>{phi_bb179_12});
    }
    if (catch372__label.is_used()) {
      compiler::CodeAssemblerLabel catch372_skip(&ca_);
      ca_.Goto(&catch372_skip);
      ca_.Bind(&catch372__label, &tmp373);
      ca_.Goto(&block188, phi_bb179_6, phi_bb179_12, phi_bb179_15, phi_bb179_16, phi_bb179_12);
      ca_.Bind(&catch372_skip);
    }
    tmp374 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp371});
    tmp375 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp365});
    tmp376 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp374}, TNode<UintPtrT>{tmp375});
    ca_.Branch(tmp376, &block193, std::vector<compiler::Node*>{phi_bb179_6, phi_bb179_12, phi_bb179_15, phi_bb179_16}, &block194, std::vector<compiler::Node*>{phi_bb179_6, phi_bb179_12, phi_bb179_15, phi_bb179_16});
  }

  TNode<IntPtrT> phi_bb186_6;
  TNode<IntPtrT> phi_bb186_12;
  TNode<JSAny> phi_bb186_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb186_16;
  TNode<Union<JSMessageObject, TheHole>> tmp377;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_6, &phi_bb186_12, &phi_bb186_15, &phi_bb186_16);
    tmp377 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp367, tmp377);
  }

  TNode<IntPtrT> phi_bb187_6;
  TNode<IntPtrT> phi_bb187_12;
  TNode<JSAny> phi_bb187_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb187_16;
  TNode<IntPtrT> phi_bb187_21;
  TNode<Union<JSMessageObject, TheHole>> tmp378;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_6, &phi_bb187_12, &phi_bb187_15, &phi_bb187_16, &phi_bb187_21);
    tmp378 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp370, tmp378);
  }

  TNode<IntPtrT> phi_bb188_6;
  TNode<IntPtrT> phi_bb188_12;
  TNode<JSAny> phi_bb188_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb188_16;
  TNode<IntPtrT> phi_bb188_21;
  TNode<Union<JSMessageObject, TheHole>> tmp379;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_6, &phi_bb188_12, &phi_bb188_15, &phi_bb188_16, &phi_bb188_21);
    tmp379 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp373, tmp379);
  }

  TNode<IntPtrT> phi_bb193_6;
  TNode<IntPtrT> phi_bb193_12;
  TNode<JSAny> phi_bb193_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb193_16;
  TNode<IntPtrT> tmp380;
  TNode<IntPtrT> tmp381;
  TNode<Union<HeapObject, TaggedIndex>> tmp382;
  TNode<IntPtrT> tmp383;
  TNode<TheHole> tmp384;
      TNode<JSAny> tmp386;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_6, &phi_bb193_12, &phi_bb193_15, &phi_bb193_16);
    tmp380 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp371});
    tmp381 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp364}, TNode<IntPtrT>{tmp380});
    std::tie(tmp382, tmp383) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp363}, TNode<IntPtrT>{tmp381}).Flatten();
    tmp384 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp382, tmp383}, tmp384);
    compiler::CodeAssemblerExceptionHandlerLabel catch385__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch385__label);
    IteratorZipCloseAll_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp48}, false);
    }
    if (catch385__label.is_used()) {
      compiler::CodeAssemblerLabel catch385_skip(&ca_);
      ca_.Goto(&catch385_skip);
      ca_.Bind(&catch385__label, &tmp386);
      ca_.Goto(&block197, phi_bb193_6, phi_bb193_12, phi_bb193_15, phi_bb193_16);
      ca_.Bind(&catch385_skip);
    }
    ca_.Goto(&block2, phi_bb193_15, phi_bb193_16);
  }

  TNode<IntPtrT> phi_bb194_6;
  TNode<IntPtrT> phi_bb194_12;
  TNode<JSAny> phi_bb194_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb194_16;
  if (block194.is_used()) {
    ca_.Bind(&block194, &phi_bb194_6, &phi_bb194_12, &phi_bb194_15, &phi_bb194_16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb197_6;
  TNode<IntPtrT> phi_bb197_12;
  TNode<JSAny> phi_bb197_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb197_16;
  TNode<Union<JSMessageObject, TheHole>> tmp387;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_6, &phi_bb197_12, &phi_bb197_15, &phi_bb197_16);
    tmp387 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp386, tmp387);
  }

  TNode<IntPtrT> phi_bb198_6;
  TNode<IntPtrT> phi_bb198_12;
  TNode<Union<JSMessageObject, TheHole>> tmp388;
  if (block198.is_used()) {
    ca_.Bind(&block198, &phi_bb198_6, &phi_bb198_12);
    tmp388 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp344, tmp388);
  }

  TNode<IntPtrT> phi_bb199_6;
  TNode<IntPtrT> phi_bb199_12;
  TNode<IntPtrT> phi_bb199_19;
  TNode<Union<JSMessageObject, TheHole>> tmp389;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_6, &phi_bb199_12, &phi_bb199_19);
    tmp389 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp347, tmp389);
  }

  TNode<IntPtrT> phi_bb200_6;
  TNode<IntPtrT> phi_bb200_12;
  TNode<IntPtrT> phi_bb200_19;
  TNode<Union<JSMessageObject, TheHole>> tmp390;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_6, &phi_bb200_12, &phi_bb200_19);
    tmp390 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp350, tmp390);
  }

  TNode<IntPtrT> phi_bb205_6;
  TNode<IntPtrT> phi_bb205_12;
  TNode<IntPtrT> tmp391;
  TNode<IntPtrT> tmp392;
  TNode<Union<HeapObject, TaggedIndex>> tmp393;
  TNode<IntPtrT> tmp394;
  TNode<TheHole> tmp395;
  TNode<IntPtrT> tmp396;
      TNode<JSAny> tmp398;
  TNode<IntPtrT> tmp399;
      TNode<JSAny> tmp401;
  if (block205.is_used()) {
    ca_.Bind(&block205, &phi_bb205_6, &phi_bb205_12);
    tmp391 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp348});
    tmp392 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp341}, TNode<IntPtrT>{tmp391});
    std::tie(tmp393, tmp394) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp340}, TNode<IntPtrT>{tmp392}).Flatten();
    tmp395 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp393, tmp394}, tmp395);
    compiler::CodeAssemblerExceptionHandlerLabel catch397__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch397__label);
    tmp396 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    }
    if (catch397__label.is_used()) {
      compiler::CodeAssemblerLabel catch397_skip(&ca_);
      ca_.Goto(&catch397_skip);
      ca_.Bind(&catch397__label, &tmp398);
      ca_.Goto(&block209, phi_bb205_6, phi_bb205_12, phi_bb205_12, phi_bb205_12);
      ca_.Bind(&catch397_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch400__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch400__label);
    tmp399 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb205_12}, TNode<IntPtrT>{tmp396});
    }
    if (catch400__label.is_used()) {
      compiler::CodeAssemblerLabel catch400_skip(&ca_);
      ca_.Goto(&catch400_skip);
      ca_.Bind(&catch400__label, &tmp401);
      ca_.Goto(&block210, phi_bb205_6, phi_bb205_12, phi_bb205_12);
      ca_.Bind(&catch400_skip);
    }
    ca_.Goto(&block136, phi_bb205_6, tmp399);
  }

  TNode<IntPtrT> phi_bb206_6;
  TNode<IntPtrT> phi_bb206_12;
  if (block206.is_used()) {
    ca_.Bind(&block206, &phi_bb206_6, &phi_bb206_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb209_6;
  TNode<IntPtrT> phi_bb209_12;
  TNode<IntPtrT> phi_bb209_13;
  TNode<IntPtrT> phi_bb209_14;
  TNode<Union<JSMessageObject, TheHole>> tmp402;
  if (block209.is_used()) {
    ca_.Bind(&block209, &phi_bb209_6, &phi_bb209_12, &phi_bb209_13, &phi_bb209_14);
    tmp402 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp398, tmp402);
  }

  TNode<IntPtrT> phi_bb210_6;
  TNode<IntPtrT> phi_bb210_12;
  TNode<IntPtrT> phi_bb210_13;
  TNode<Union<JSMessageObject, TheHole>> tmp403;
  if (block210.is_used()) {
    ca_.Bind(&block210, &phi_bb210_6, &phi_bb210_12, &phi_bb210_13);
    tmp403 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp401, tmp403);
  }

  TNode<IntPtrT> phi_bb135_6;
  TNode<IntPtrT> phi_bb135_12;
      TNode<JSAny> tmp405;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_6, &phi_bb135_12);
    compiler::CodeAssemblerExceptionHandlerLabel catch404__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch404__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    }
    if (catch404__label.is_used()) {
      compiler::CodeAssemblerLabel catch404_skip(&ca_);
      ca_.Goto(&catch404_skip);
      ca_.Bind(&catch404__label, &tmp405);
      ca_.Goto(&block211, phi_bb135_6);
      ca_.Bind(&catch404_skip);
    }
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> phi_bb211_6;
  TNode<Union<JSMessageObject, TheHole>> tmp406;
  if (block211.is_used()) {
    ca_.Bind(&block211, &phi_bb211_6);
    tmp406 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp405, tmp406);
  }

  TNode<IntPtrT> phi_bb122_6;
  TNode<Uint32T> tmp407;
      TNode<JSAny> tmp409;
  TNode<BoolT> tmp410;
      TNode<JSAny> tmp412;
  if (block122.is_used()) {
    ca_.Bind(&block122, &phi_bb122_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch408__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch408__label);
    tmp407 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kLongest));
    }
    if (catch408__label.is_used()) {
      compiler::CodeAssemblerLabel catch408_skip(&ca_);
      ca_.Goto(&catch408_skip);
      ca_.Bind(&catch408__label, &tmp409);
      ca_.Goto(&block214, phi_bb122_6);
      ca_.Bind(&catch408_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch411__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch411__label);
    tmp410 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp13}, TNode<Uint32T>{tmp407});
    }
    if (catch411__label.is_used()) {
      compiler::CodeAssemblerLabel catch411_skip(&ca_);
      ca_.Goto(&catch411_skip);
      ca_.Bind(&catch411__label, &tmp412);
      ca_.Goto(&block215, phi_bb122_6);
      ca_.Bind(&catch411_skip);
    }
    ca_.Branch(tmp410, &block212, std::vector<compiler::Node*>{phi_bb122_6}, &block213, std::vector<compiler::Node*>{phi_bb122_6});
  }

  TNode<IntPtrT> phi_bb214_6;
  TNode<Union<JSMessageObject, TheHole>> tmp413;
  if (block214.is_used()) {
    ca_.Bind(&block214, &phi_bb214_6);
    tmp413 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp409, tmp413);
  }

  TNode<IntPtrT> phi_bb215_6;
  TNode<Union<JSMessageObject, TheHole>> tmp414;
  if (block215.is_used()) {
    ca_.Bind(&block215, &phi_bb215_6);
    tmp414 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp412, tmp414);
  }

  TNode<IntPtrT> phi_bb213_6;
  if (block213.is_used()) {
    ca_.Bind(&block213, &phi_bb213_6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1813});
      CodeStubAssembler(state_).FailAssert("Torque assert 'mode == JSIteratorZipHelperMode::kLongest' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb212_6;
  TNode<IntPtrT> tmp415;
      TNode<JSAny> tmp417;
  TNode<Smi> tmp418;
  TNode<Smi> tmp419;
      TNode<JSAny> tmp421;
  TNode<BoolT> tmp422;
      TNode<JSAny> tmp424;
  if (block212.is_used()) {
    ca_.Bind(&block212, &phi_bb212_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch416__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch416__label);
    tmp415 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    }
    if (catch416__label.is_used()) {
      compiler::CodeAssemblerLabel catch416_skip(&ca_);
      ca_.Goto(&catch416_skip);
      ca_.Bind(&catch416__label, &tmp417);
      ca_.Goto(&block218, phi_bb212_6);
      ca_.Bind(&catch416_skip);
    }
    tmp418 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_helper, tmp415});
    compiler::CodeAssemblerExceptionHandlerLabel catch420__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch420__label);
    tmp419 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    }
    if (catch420__label.is_used()) {
      compiler::CodeAssemblerLabel catch420_skip(&ca_);
      ca_.Goto(&catch420_skip);
      ca_.Bind(&catch420__label, &tmp421);
      ca_.Goto(&block219, phi_bb212_6);
      ca_.Bind(&catch420_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch423__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch423__label);
    tmp422 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp418}, TNode<Smi>{tmp419});
    }
    if (catch423__label.is_used()) {
      compiler::CodeAssemblerLabel catch423_skip(&ca_);
      ca_.Goto(&catch423_skip);
      ca_.Bind(&catch423__label, &tmp424);
      ca_.Goto(&block220, phi_bb212_6);
      ca_.Bind(&catch423_skip);
    }
    ca_.Branch(tmp422, &block216, std::vector<compiler::Node*>{phi_bb212_6}, &block217, std::vector<compiler::Node*>{phi_bb212_6});
  }

  TNode<IntPtrT> phi_bb218_6;
  TNode<Union<JSMessageObject, TheHole>> tmp425;
  if (block218.is_used()) {
    ca_.Bind(&block218, &phi_bb218_6);
    tmp425 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp417, tmp425);
  }

  TNode<IntPtrT> phi_bb219_6;
  TNode<Union<JSMessageObject, TheHole>> tmp426;
  if (block219.is_used()) {
    ca_.Bind(&block219, &phi_bb219_6);
    tmp426 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp421, tmp426);
  }

  TNode<IntPtrT> phi_bb220_6;
  TNode<Union<JSMessageObject, TheHole>> tmp427;
  if (block220.is_used()) {
    ca_.Bind(&block220, &phi_bb220_6);
    tmp427 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp424, tmp427);
  }

  TNode<IntPtrT> phi_bb216_6;
      TNode<JSAny> tmp429;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch428__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch428__label);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    }
    if (catch428__label.is_used()) {
      compiler::CodeAssemblerLabel catch428_skip(&ca_);
      ca_.Goto(&catch428_skip);
      ca_.Bind(&catch428__label, &tmp429);
      ca_.Goto(&block221, phi_bb216_6);
      ca_.Bind(&catch428_skip);
    }
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> phi_bb221_6;
  TNode<Union<JSMessageObject, TheHole>> tmp430;
  if (block221.is_used()) {
    ca_.Bind(&block221, &phi_bb221_6);
    tmp430 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp429, tmp430);
  }

  TNode<IntPtrT> phi_bb217_6;
  TNode<IntPtrT> tmp431;
      TNode<JSAny> tmp433;
  TNode<FixedArray> tmp434;
  TNode<Union<HeapObject, TaggedIndex>> tmp435;
  TNode<IntPtrT> tmp436;
  TNode<IntPtrT> tmp437;
      TNode<JSAny> tmp439;
  TNode<UintPtrT> tmp440;
  TNode<UintPtrT> tmp441;
  TNode<BoolT> tmp442;
  if (block217.is_used()) {
    ca_.Bind(&block217, &phi_bb217_6);
    compiler::CodeAssemblerExceptionHandlerLabel catch432__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch432__label);
    tmp431 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    }
    if (catch432__label.is_used()) {
      compiler::CodeAssemblerLabel catch432_skip(&ca_);
      ca_.Goto(&catch432_skip);
      ca_.Bind(&catch432__label, &tmp433);
      ca_.Goto(&block224, phi_bb217_6);
      ca_.Bind(&catch432_skip);
    }
    tmp434 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_helper, tmp431});
    compiler::CodeAssemblerExceptionHandlerLabel catch438__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch438__label);
    std::tie(tmp435, tmp436, tmp437) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp434}).Flatten();
    }
    if (catch438__label.is_used()) {
      compiler::CodeAssemblerLabel catch438_skip(&ca_);
      ca_.Goto(&catch438_skip);
      ca_.Bind(&catch438__label, &tmp439);
      ca_.Goto(&block225, phi_bb217_6);
      ca_.Bind(&catch438_skip);
    }
    tmp440 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb217_6});
    tmp441 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp437});
    tmp442 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp440}, TNode<UintPtrT>{tmp441});
    ca_.Branch(tmp442, &block230, std::vector<compiler::Node*>{phi_bb217_6, phi_bb217_6, phi_bb217_6, phi_bb217_6, phi_bb217_6}, &block231, std::vector<compiler::Node*>{phi_bb217_6, phi_bb217_6, phi_bb217_6, phi_bb217_6, phi_bb217_6});
  }

  TNode<IntPtrT> phi_bb224_6;
  TNode<Union<JSMessageObject, TheHole>> tmp443;
  if (block224.is_used()) {
    ca_.Bind(&block224, &phi_bb224_6);
    tmp443 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp433, tmp443);
  }

  TNode<IntPtrT> phi_bb225_6;
  TNode<Union<JSMessageObject, TheHole>> tmp444;
  if (block225.is_used()) {
    ca_.Bind(&block225, &phi_bb225_6);
    tmp444 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp439, tmp444);
  }

  TNode<IntPtrT> phi_bb230_6;
  TNode<IntPtrT> phi_bb230_19;
  TNode<IntPtrT> phi_bb230_20;
  TNode<IntPtrT> phi_bb230_24;
  TNode<IntPtrT> phi_bb230_25;
  TNode<IntPtrT> tmp445;
  TNode<IntPtrT> tmp446;
  TNode<Union<HeapObject, TaggedIndex>> tmp447;
  TNode<IntPtrT> tmp448;
  TNode<Object> tmp449;
  TNode<JSAny> tmp450;
      TNode<JSAny> tmp453;
  if (block230.is_used()) {
    ca_.Bind(&block230, &phi_bb230_6, &phi_bb230_19, &phi_bb230_20, &phi_bb230_24, &phi_bb230_25);
    tmp445 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb230_25});
    tmp446 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp436}, TNode<IntPtrT>{tmp445});
    std::tie(tmp447, tmp448) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp435}, TNode<IntPtrT>{tmp446}).Flatten();
    tmp449 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp447, tmp448});
    compiler::CodeAssemblerLabel label451(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch452__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch452__label);
    tmp450 = Cast_JSAny_0(state_, TNode<Object>{tmp449}, &label451);
    }
    if (catch452__label.is_used()) {
      compiler::CodeAssemblerLabel catch452_skip(&ca_);
      ca_.Goto(&catch452_skip);
      ca_.Bind(&catch452__label, &tmp453);
      ca_.Goto(&block236, phi_bb230_6);
      ca_.Bind(&catch452_skip);
    }
    ca_.Goto(&block234, phi_bb230_6);
    if (label451.is_used()) {
      ca_.Bind(&label451);
      ca_.Goto(&block235, phi_bb230_6);
    }
  }

  TNode<IntPtrT> phi_bb231_6;
  TNode<IntPtrT> phi_bb231_19;
  TNode<IntPtrT> phi_bb231_20;
  TNode<IntPtrT> phi_bb231_24;
  TNode<IntPtrT> phi_bb231_25;
  if (block231.is_used()) {
    ca_.Bind(&block231, &phi_bb231_6, &phi_bb231_19, &phi_bb231_20, &phi_bb231_24, &phi_bb231_25);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb236_6;
  TNode<Union<JSMessageObject, TheHole>> tmp454;
  if (block236.is_used()) {
    ca_.Bind(&block236, &phi_bb236_6);
    tmp454 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp453, tmp454);
  }

  TNode<IntPtrT> phi_bb235_6;
  if (block235.is_used()) {
    ca_.Bind(&block235, &phi_bb235_6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1823:66");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb234_6;
  if (block234.is_used()) {
    ca_.Bind(&block234, &phi_bb234_6);
    ca_.Goto(&block79, phi_bb234_6, tmp450);
  }

  TNode<IntPtrT> phi_bb79_6;
  TNode<JSAny> phi_bb79_7;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_6, &phi_bb79_7);
    ca_.Goto(&block54, phi_bb79_6, phi_bb79_7);
  }

  TNode<IntPtrT> phi_bb54_6;
  TNode<JSAny> phi_bb54_7;
  TNode<Union<HeapObject, TaggedIndex>> tmp455;
  TNode<IntPtrT> tmp456;
  TNode<IntPtrT> tmp457;
      TNode<JSAny> tmp459;
  TNode<UintPtrT> tmp460;
  TNode<UintPtrT> tmp461;
  TNode<BoolT> tmp462;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_6, &phi_bb54_7);
    compiler::CodeAssemblerExceptionHandlerLabel catch458__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch458__label);
    std::tie(tmp455, tmp456, tmp457) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp15}).Flatten();
    }
    if (catch458__label.is_used()) {
      compiler::CodeAssemblerLabel catch458_skip(&ca_);
      ca_.Goto(&catch458_skip);
      ca_.Bind(&catch458__label, &tmp459);
      ca_.Goto(&block237, phi_bb54_6);
      ca_.Bind(&catch458_skip);
    }
    tmp460 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb54_6});
    tmp461 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp457});
    tmp462 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp460}, TNode<UintPtrT>{tmp461});
    ca_.Branch(tmp462, &block242, std::vector<compiler::Node*>{phi_bb54_6, phi_bb54_6, phi_bb54_6, phi_bb54_6, phi_bb54_6}, &block243, std::vector<compiler::Node*>{phi_bb54_6, phi_bb54_6, phi_bb54_6, phi_bb54_6, phi_bb54_6});
  }

  TNode<IntPtrT> phi_bb237_6;
  TNode<Union<JSMessageObject, TheHole>> tmp463;
  if (block237.is_used()) {
    ca_.Bind(&block237, &phi_bb237_6);
    tmp463 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp459, tmp463);
  }

  TNode<IntPtrT> phi_bb242_6;
  TNode<IntPtrT> phi_bb242_15;
  TNode<IntPtrT> phi_bb242_16;
  TNode<IntPtrT> phi_bb242_20;
  TNode<IntPtrT> phi_bb242_21;
  TNode<IntPtrT> tmp464;
  TNode<IntPtrT> tmp465;
  TNode<Union<HeapObject, TaggedIndex>> tmp466;
  TNode<IntPtrT> tmp467;
  TNode<IntPtrT> tmp468;
      TNode<JSAny> tmp470;
  TNode<IntPtrT> tmp471;
      TNode<JSAny> tmp473;
  if (block242.is_used()) {
    ca_.Bind(&block242, &phi_bb242_6, &phi_bb242_15, &phi_bb242_16, &phi_bb242_20, &phi_bb242_21);
    tmp464 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb242_21});
    tmp465 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp456}, TNode<IntPtrT>{tmp464});
    std::tie(tmp466, tmp467) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp455}, TNode<IntPtrT>{tmp465}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp466, tmp467}, phi_bb54_7);
    compiler::CodeAssemblerExceptionHandlerLabel catch469__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch469__label);
    tmp468 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    }
    if (catch469__label.is_used()) {
      compiler::CodeAssemblerLabel catch469_skip(&ca_);
      ca_.Goto(&catch469_skip);
      ca_.Bind(&catch469__label, &tmp470);
      ca_.Goto(&block246, phi_bb242_6, phi_bb242_6, phi_bb242_6);
      ca_.Bind(&catch469_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch472__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch472__label);
    tmp471 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb242_6}, TNode<IntPtrT>{tmp468});
    }
    if (catch472__label.is_used()) {
      compiler::CodeAssemblerLabel catch472_skip(&ca_);
      ca_.Goto(&catch472_skip);
      ca_.Bind(&catch472__label, &tmp473);
      ca_.Goto(&block247, phi_bb242_6, phi_bb242_6);
      ca_.Bind(&catch472_skip);
    }
    ca_.Goto(&block18, tmp471);
  }

  TNode<IntPtrT> phi_bb243_6;
  TNode<IntPtrT> phi_bb243_15;
  TNode<IntPtrT> phi_bb243_16;
  TNode<IntPtrT> phi_bb243_20;
  TNode<IntPtrT> phi_bb243_21;
  if (block243.is_used()) {
    ca_.Bind(&block243, &phi_bb243_6, &phi_bb243_15, &phi_bb243_16, &phi_bb243_20, &phi_bb243_21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb246_6;
  TNode<IntPtrT> phi_bb246_7;
  TNode<IntPtrT> phi_bb246_8;
  TNode<Union<JSMessageObject, TheHole>> tmp474;
  if (block246.is_used()) {
    ca_.Bind(&block246, &phi_bb246_6, &phi_bb246_7, &phi_bb246_8);
    tmp474 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp470, tmp474);
  }

  TNode<IntPtrT> phi_bb247_6;
  TNode<IntPtrT> phi_bb247_7;
  TNode<Union<JSMessageObject, TheHole>> tmp475;
  if (block247.is_used()) {
    ca_.Bind(&block247, &phi_bb247_6, &phi_bb247_7);
    tmp475 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block7, tmp473, tmp475);
  }

  TNode<IntPtrT> phi_bb17_6;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_6);
    ca_.Goto(&block248);
  }

  TNode<JSAny> phi_bb7_5;
  TNode<Union<JSMessageObject, TheHole>> phi_bb7_6;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5, &phi_bb7_6);
    MarkIteratorHelperAsExhausted_0(state_, TNode<JSIteratorHelper>{p_helper});
    ca_.Goto(&block2, phi_bb7_5, phi_bb7_6);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Done);
  }

  TNode<JSAny> phi_bb2_0;
  TNode<Union<JSMessageObject, TheHole>> phi_bb2_1;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_0, &phi_bb2_1);
    *label_DoneWithException_parameter_1 = phi_bb2_1;
    *label_DoneWithException_parameter_0 = phi_bb2_0;
    ca_.Goto(label_DoneWithException);
  }

    ca_.Bind(&block248);
  return TNode<FixedArray>{tmp15};
}

TF_BUILTIN(IteratorZipHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorZipHelper> parameter1 = UncheckedParameter<JSIteratorZipHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp3(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp4(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp0 = IteratorZipHelperNextCommon_0(state_, TNode<Context>{parameter0}, TNode<JSIteratorZipHelper>{parameter1}, "Iterator.zip", &label1, &label2, &tmp3, &tmp4);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  TNode<Undefined> tmp5;
  TNode<True> tmp6;
  TNode<JSObject> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp5 = Undefined_0(state_);
    tmp6 = True_0(state_);
    tmp7 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp5}, TNode<Boolean>{tmp6});
    CodeStubAssembler(state_).Return(tmp7);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp3.value(), tmp4.value());
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Map> tmp8;
  TNode<JSArray> tmp9;
  TNode<False> tmp10;
  TNode<JSObject> tmp11;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp8 = GetFastPackedElementsJSArrayMap_0(state_, TNode<Context>{parameter0});
    tmp9 = NewJSArray_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp8}, TNode<FixedArrayBase>{tmp0});
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp10 = False_0(state_);
    tmp11 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp9}, TNode<Boolean>{tmp10});
    CodeStubAssembler(state_).Return(tmp11);
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1865&c=1
TNode<JSIteratorZipKeyedHelper> NewJSIteratorZipKeyedHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterators, TNode<FixedArray> p_padding, TNode<Uint32T> p_zipMode, TNode<FixedArray> p_keys) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Uint32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{p_iterators, tmp0});
    tmp2 = FromConstexpr_uint32_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp3 = CodeStubAssembler(state_).Uint32Mod(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp2});
    tmp4 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp3}, TNode<Uint32T>{tmp4});
    ca_.Branch(tmp5, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/iterator-helpers.tq", 1869});
      CodeStubAssembler(state_).FailAssert("Torque assert 'iterators.length % kIteratorRecordFieldCount == 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<Union<HeapObject, TaggedIndex>> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<FixedArray> tmp10;
  TNode<FixedArray> tmp11;
  TNode<Uint32T> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Smi> tmp18;
  TNode<BoolT> tmp19;
  TNode<BoolT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<HeapObject> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<JSIteratorZipKeyedHelper> tmp32;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp6 = ITERATOR_ZIP_KEYED_HELPER_MAP_INDEX_0(state_);
    std::tie(tmp7, tmp8) = NativeContextSlot_Context_Map_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp6}).Flatten();
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp7, tmp8});
    tmp10 = kEmptyFixedArray_0(state_);
    tmp11 = kEmptyFixedArray_0(state_);
    tmp12 = FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(state_, JSIteratorHelperState::kSuspendedStart);
    tmp13 = SmiTag_JSIteratorHelperState_0(state_, TNode<Uint32T>{tmp12});
    tmp14 = SmiTag_JSIteratorZipHelperMode_0(state_, TNode<Uint32T>{p_zipMode});
    tmp15 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{p_iterators});
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp17 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp16});
    tmp18 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{tmp17});
    tmp19 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp22 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp21}, TNode<Map>{tmp9}, TNode<BoolT>{tmp19}, TNode<BoolT>{tmp20});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp22, tmp23}, tmp9);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp22, tmp24}, tmp10);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp22, tmp25}, tmp11);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp26}, tmp13);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp22, tmp27}, p_iterators);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp28}, tmp14);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp29}, tmp18);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp22, tmp30}, p_padding);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp22, tmp31}, p_keys);
    tmp32 = TORQUE_CAST(TNode<HeapObject>{tmp22});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSIteratorZipKeyedHelper>{tmp32};
}

TF_BUILTIN(IteratorZipKeyed, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, BoolT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, UintPtrT, UintPtrT> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, UintPtrT, UintPtrT> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block58(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block61(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block65(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block66(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, BoolT> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block67(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block70(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block74(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block79(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block81(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block83(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block96(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block97(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block98(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block102(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block107(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block109(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block111(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, UintPtrT> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block123(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block122(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block124(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, FixedArray, IntPtrT, UintPtrT> block128(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, FixedArray, IntPtrT, UintPtrT> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, FixedArray, IntPtrT, UintPtrT> block130(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, FixedArray, IntPtrT, UintPtrT> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, FixedArray, IntPtrT, UintPtrT> block132(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, FixedArray, IntPtrT, UintPtrT> block131(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT> block125(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT, FixedArray> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, FixedArray, IntPtrT, UintPtrT, FixedArray> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, JSAny, Union<JSMessageObject, TheHole>> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, IntPtrT, IntPtrT> block143(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, IntPtrT, IntPtrT> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, IntPtrT, IntPtrT> block145(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, IntPtrT, IntPtrT> block144(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, IntPtrT, IntPtrT> block147(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT, IntPtrT, IntPtrT> block146(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, UintPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block148(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT> block154(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block163(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT> block170(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, JSAny> block179(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block182(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block181(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block184(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block186(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, JSAny, Union<JSMessageObject, TheHole>, IntPtrT, IntPtrT> block185(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block189(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block191(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block193(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block196(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block198(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block197(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block200(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Uint32T, JSAny, FixedArray, IntPtrT, IntPtrT, FixedArray, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<JSReceiver> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, &label3);
    ca_.Goto(&block3);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Iterator.zipKeyed");
  }

  TNode<IntPtrT> tmp4;
  TNode<JSAny> tmp5;
  TNode<JSReceiver> tmp6;
  TNode<Uint32T> tmp7;
  TNode<JSAny> tmp8;
  TNode<JSAny> tmp9;
  TNode<Undefined> tmp10;
  TNode<BoolT> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp5 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp4});
    tmp6 = GetOptionsObject_0(state_, TNode<NativeContext>{parameter0}, TNode<JSAny>{tmp5});
    tmp7 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kShortest_0(state_, JSIteratorZipHelperMode::kShortest);
    tmp8 = FromConstexpr_JSAny_constexpr_string_0(state_, "mode");
    tmp9 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp6}, TNode<JSAny>{tmp8});
    tmp10 = Undefined_0(state_);
    tmp11 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp9}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp10});
    ca_.Branch(tmp11, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{tmp7});
  }

  TNode<String> tmp12;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = Cast_String_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp9}, &label13);
    ca_.Goto(&block9);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidIteratorZipMode), "Iterator.zipKeyed");
  }

  TNode<String> tmp14;
  TNode<Oddball> tmp15;
  TNode<True> tmp16;
  TNode<BoolT> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp14 = CodeStubAssembler(state_).StringConstant("shortest");
    tmp15 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kStringEqual, parameter0, tmp12, tmp14)); 
    tmp16 = True_0(state_);
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp15}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp16});
    ca_.Branch(tmp17, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp18;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp18 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kShortest_0(state_, JSIteratorZipHelperMode::kShortest);
    ca_.Goto(&block13, tmp18);
  }

  TNode<String> tmp19;
  TNode<Oddball> tmp20;
  TNode<True> tmp21;
  TNode<BoolT> tmp22;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp19 = CodeStubAssembler(state_).StringConstant("longest");
    tmp20 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kStringEqual, parameter0, tmp12, tmp19)); 
    tmp21 = True_0(state_);
    tmp22 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp20}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp21});
    ca_.Branch(tmp22, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp23;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp23 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kLongest_0(state_, JSIteratorZipHelperMode::kLongest);
    ca_.Goto(&block16, tmp23);
  }

  TNode<String> tmp24;
  TNode<Oddball> tmp25;
  TNode<True> tmp26;
  TNode<BoolT> tmp27;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp24 = CodeStubAssembler(state_).StringConstant("strict");
    tmp25 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kStringEqual, parameter0, tmp12, tmp24)); 
    tmp26 = True_0(state_);
    tmp27 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp25}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp26});
    ca_.Branch(tmp27, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp28;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp28 = FromConstexpr_JSIteratorZipHelperMode_constexpr_kStrict_0(state_, JSIteratorZipHelperMode::kStrict);
    ca_.Goto(&block16, tmp28);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidIteratorZipMode), "Iterator.zipKeyed");
  }

  TNode<Uint32T> phi_bb16_9;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_9);
    ca_.Goto(&block13, phi_bb16_9);
  }

  TNode<Uint32T> phi_bb13_9;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_9);
    ca_.Goto(&block6, phi_bb13_9);
  }

  TNode<Uint32T> phi_bb6_9;
  TNode<Undefined> tmp29;
  TNode<Uint32T> tmp30;
  TNode<BoolT> tmp31;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_9);
    tmp29 = Undefined_0(state_);
    tmp30 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kLongest));
    tmp31 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{phi_bb6_9}, TNode<Uint32T>{tmp30});
    ca_.Branch(tmp31, &block20, std::vector<compiler::Node*>{phi_bb6_9}, &block21, std::vector<compiler::Node*>{phi_bb6_9, tmp29});
  }

  TNode<Uint32T> phi_bb20_9;
  TNode<JSAny> tmp32;
  TNode<JSAny> tmp33;
  TNode<Undefined> tmp34;
  TNode<BoolT> tmp35;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_9);
    tmp32 = FromConstexpr_JSAny_constexpr_string_0(state_, "padding");
    tmp33 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp6}, TNode<JSAny>{tmp32});
    tmp34 = Undefined_0(state_);
    tmp35 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp33}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp34});
    ca_.Branch(tmp35, &block24, std::vector<compiler::Node*>{phi_bb20_9}, &block25, std::vector<compiler::Node*>{phi_bb20_9});
  }

  TNode<Uint32T> phi_bb24_9;
  TNode<BoolT> tmp36;
  TNode<BoolT> tmp37;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_9);
    tmp36 = Is_JSReceiver_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp33});
    tmp37 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp36});
    ca_.Goto(&block26, phi_bb24_9, tmp37);
  }

  TNode<Uint32T> phi_bb25_9;
  TNode<BoolT> tmp38;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_9);
    tmp38 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block26, phi_bb25_9, tmp38);
  }

  TNode<Uint32T> phi_bb26_9;
  TNode<BoolT> phi_bb26_13;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_9, &phi_bb26_13);
    ca_.Branch(phi_bb26_13, &block22, std::vector<compiler::Node*>{phi_bb26_9}, &block23, std::vector<compiler::Node*>{phi_bb26_9});
  }

  TNode<Uint32T> phi_bb22_9;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_9);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "padding");
  }

  TNode<Uint32T> phi_bb23_9;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_9);
    ca_.Goto(&block21, phi_bb23_9, tmp33);
  }

  TNode<Uint32T> phi_bb21_9;
  TNode<JSAny> phi_bb21_11;
  TNode<FixedArray> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<FixedArray> tmp42;
  TNode<Smi> tmp43;
  TNode<JSArray> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<FixedArrayBase> tmp46;
  TNode<FixedArray> tmp47;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_9, &phi_bb21_11);
    std::tie(tmp39, tmp40, tmp41) = NewGrowableFixedArray_0(state_).Flatten();
    tmp42 = kEmptyFixedArray_0(state_);
    tmp43 = SmiConstant_0(state_, IntegerLiteral(false, 0x0ull));
    tmp44 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kGetOwnPropertyKeys, parameter0, tmp2, tmp43)); 
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp46 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp44, tmp45});
    compiler::CodeAssemblerLabel label48(&ca_);
    tmp47 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp46}, &label48);
    ca_.Goto(&block29, phi_bb21_9, phi_bb21_11);
    if (label48.is_used()) {
      ca_.Bind(&label48);
      ca_.Goto(&block30, phi_bb21_9, phi_bb21_11);
    }
  }

  TNode<Uint32T> phi_bb30_9;
  TNode<JSAny> phi_bb30_11;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_9, &phi_bb30_11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1942:59");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb29_9;
  TNode<JSAny> phi_bb29_11;
  TNode<FixedArray> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<Number> tmp53;
  TNode<UintPtrT> tmp54;
  TNode<UintPtrT> tmp55;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_9, &phi_bb29_11);
    std::tie(tmp49, tmp50, tmp51) = NewGrowableFixedArray_0(state_).Flatten();
    tmp52 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp53 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp44, tmp52});
    tmp54 = Convert_uintptr_Number_0(state_, TNode<Number>{tmp53});
    tmp55 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block33, phi_bb29_9, phi_bb29_11, tmp39, tmp40, tmp41, tmp49, tmp50, tmp51, tmp55);
  }

  TNode<Uint32T> phi_bb33_9;
  TNode<JSAny> phi_bb33_11;
  TNode<FixedArray> phi_bb33_12;
  TNode<IntPtrT> phi_bb33_13;
  TNode<IntPtrT> phi_bb33_14;
  TNode<FixedArray> phi_bb33_18;
  TNode<IntPtrT> phi_bb33_19;
  TNode<IntPtrT> phi_bb33_20;
  TNode<UintPtrT> phi_bb33_22;
  TNode<BoolT> tmp56;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_9, &phi_bb33_11, &phi_bb33_12, &phi_bb33_13, &phi_bb33_14, &phi_bb33_18, &phi_bb33_19, &phi_bb33_20, &phi_bb33_22);
    tmp56 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb33_22}, TNode<UintPtrT>{tmp54});
    ca_.Branch(tmp56, &block31, std::vector<compiler::Node*>{phi_bb33_9, phi_bb33_11, phi_bb33_12, phi_bb33_13, phi_bb33_14, phi_bb33_18, phi_bb33_19, phi_bb33_20, phi_bb33_22}, &block32, std::vector<compiler::Node*>{phi_bb33_9, phi_bb33_11, phi_bb33_12, phi_bb33_13, phi_bb33_14, phi_bb33_18, phi_bb33_19, phi_bb33_20, phi_bb33_22});
  }

  TNode<Uint32T> phi_bb31_9;
  TNode<JSAny> phi_bb31_11;
  TNode<FixedArray> phi_bb31_12;
  TNode<IntPtrT> phi_bb31_13;
  TNode<IntPtrT> phi_bb31_14;
  TNode<FixedArray> phi_bb31_18;
  TNode<IntPtrT> phi_bb31_19;
  TNode<IntPtrT> phi_bb31_20;
  TNode<UintPtrT> phi_bb31_22;
  TNode<Union<HeapObject, TaggedIndex>> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<UintPtrT> tmp61;
  TNode<UintPtrT> tmp62;
  TNode<BoolT> tmp63;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_9, &phi_bb31_11, &phi_bb31_12, &phi_bb31_13, &phi_bb31_14, &phi_bb31_18, &phi_bb31_19, &phi_bb31_20, &phi_bb31_22);
    std::tie(tmp57, tmp58, tmp59) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp47}).Flatten();
    tmp60 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb31_22});
    tmp61 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp60});
    tmp62 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp59});
    tmp63 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp61}, TNode<UintPtrT>{tmp62});
    ca_.Branch(tmp63, &block41, std::vector<compiler::Node*>{phi_bb31_9, phi_bb31_11, phi_bb31_12, phi_bb31_13, phi_bb31_14, phi_bb31_18, phi_bb31_19, phi_bb31_20, phi_bb31_22, phi_bb31_22, phi_bb31_22}, &block42, std::vector<compiler::Node*>{phi_bb31_9, phi_bb31_11, phi_bb31_12, phi_bb31_13, phi_bb31_14, phi_bb31_18, phi_bb31_19, phi_bb31_20, phi_bb31_22, phi_bb31_22, phi_bb31_22});
  }

  TNode<Uint32T> phi_bb41_9;
  TNode<JSAny> phi_bb41_11;
  TNode<FixedArray> phi_bb41_12;
  TNode<IntPtrT> phi_bb41_13;
  TNode<IntPtrT> phi_bb41_14;
  TNode<FixedArray> phi_bb41_18;
  TNode<IntPtrT> phi_bb41_19;
  TNode<IntPtrT> phi_bb41_20;
  TNode<UintPtrT> phi_bb41_22;
  TNode<UintPtrT> phi_bb41_27;
  TNode<UintPtrT> phi_bb41_28;
  TNode<IntPtrT> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<Union<HeapObject, TaggedIndex>> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<Object> tmp68;
  TNode<JSAny> tmp69;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_9, &phi_bb41_11, &phi_bb41_12, &phi_bb41_13, &phi_bb41_14, &phi_bb41_18, &phi_bb41_19, &phi_bb41_20, &phi_bb41_22, &phi_bb41_27, &phi_bb41_28);
    tmp64 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp60});
    tmp65 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp58}, TNode<IntPtrT>{tmp64});
    std::tie(tmp66, tmp67) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp57}, TNode<IntPtrT>{tmp65}).Flatten();
    tmp68 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp66, tmp67});
    compiler::CodeAssemblerLabel label70(&ca_);
    tmp69 = Cast_JSAny_0(state_, TNode<Object>{tmp68}, &label70);
    ca_.Goto(&block45, phi_bb41_9, phi_bb41_11, phi_bb41_12, phi_bb41_13, phi_bb41_14, phi_bb41_18, phi_bb41_19, phi_bb41_20, phi_bb41_22);
    if (label70.is_used()) {
      ca_.Bind(&label70);
      ca_.Goto(&block46, phi_bb41_9, phi_bb41_11, phi_bb41_12, phi_bb41_13, phi_bb41_14, phi_bb41_18, phi_bb41_19, phi_bb41_20, phi_bb41_22);
    }
  }

  TNode<Uint32T> phi_bb42_9;
  TNode<JSAny> phi_bb42_11;
  TNode<FixedArray> phi_bb42_12;
  TNode<IntPtrT> phi_bb42_13;
  TNode<IntPtrT> phi_bb42_14;
  TNode<FixedArray> phi_bb42_18;
  TNode<IntPtrT> phi_bb42_19;
  TNode<IntPtrT> phi_bb42_20;
  TNode<UintPtrT> phi_bb42_22;
  TNode<UintPtrT> phi_bb42_27;
  TNode<UintPtrT> phi_bb42_28;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_9, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13, &phi_bb42_14, &phi_bb42_18, &phi_bb42_19, &phi_bb42_20, &phi_bb42_22, &phi_bb42_27, &phi_bb42_28);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb46_9;
  TNode<JSAny> phi_bb46_11;
  TNode<FixedArray> phi_bb46_12;
  TNode<IntPtrT> phi_bb46_13;
  TNode<IntPtrT> phi_bb46_14;
  TNode<FixedArray> phi_bb46_18;
  TNode<IntPtrT> phi_bb46_19;
  TNode<IntPtrT> phi_bb46_20;
  TNode<UintPtrT> phi_bb46_22;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_9, &phi_bb46_11, &phi_bb46_12, &phi_bb46_13, &phi_bb46_14, &phi_bb46_18, &phi_bb46_19, &phi_bb46_20, &phi_bb46_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1950:59");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb45_9;
  TNode<JSAny> phi_bb45_11;
  TNode<FixedArray> phi_bb45_12;
  TNode<IntPtrT> phi_bb45_13;
  TNode<IntPtrT> phi_bb45_14;
  TNode<FixedArray> phi_bb45_18;
  TNode<IntPtrT> phi_bb45_19;
  TNode<IntPtrT> phi_bb45_20;
  TNode<UintPtrT> phi_bb45_22;
  TNode<Union<String, Symbol>> tmp71;
      TNode<JSAny> tmp73;
  TNode<JSAny> tmp74;
      TNode<JSAny> tmp76;
  TNode<Undefined> tmp77;
  TNode<BoolT> tmp78;
      TNode<JSAny> tmp80;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_9, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_14, &phi_bb45_18, &phi_bb45_19, &phi_bb45_20, &phi_bb45_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch72__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch72__label);
    tmp71 = ca_.CallBuiltin<Union<String, Symbol>>(Builtin::kToName, parameter0, tmp69);
    }
    if (catch72__label.is_used()) {
      compiler::CodeAssemblerLabel catch72_skip(&ca_);
      ca_.Goto(&catch72_skip);
      ca_.Bind(&catch72__label, &tmp73);
      ca_.Goto(&block49, phi_bb45_9, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_18, phi_bb45_19, phi_bb45_20, phi_bb45_22);
      ca_.Bind(&catch72_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch75__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch75__label);
    tmp74 = ca_.CallBuiltin<JSAny>(Builtin::kGetOwnPropertyDescriptor, parameter0, tmp2, tmp71);
    }
    if (catch75__label.is_used()) {
      compiler::CodeAssemblerLabel catch75_skip(&ca_);
      ca_.Goto(&catch75_skip);
      ca_.Bind(&catch75__label, &tmp76);
      ca_.Goto(&block50, phi_bb45_9, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_18, phi_bb45_19, phi_bb45_20, phi_bb45_22);
      ca_.Bind(&catch75_skip);
    }
    tmp77 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch79__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch79__label);
    tmp78 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp74}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp77});
    }
    if (catch79__label.is_used()) {
      compiler::CodeAssemblerLabel catch79_skip(&ca_);
      ca_.Goto(&catch79_skip);
      ca_.Bind(&catch79__label, &tmp80);
      ca_.Goto(&block53, phi_bb45_9, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_18, phi_bb45_19, phi_bb45_20, phi_bb45_22);
      ca_.Bind(&catch79_skip);
    }
    ca_.Branch(tmp78, &block51, std::vector<compiler::Node*>{phi_bb45_9, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_18, phi_bb45_19, phi_bb45_20, phi_bb45_22}, &block52, std::vector<compiler::Node*>{phi_bb45_9, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_18, phi_bb45_19, phi_bb45_20, phi_bb45_22});
  }

  TNode<Uint32T> phi_bb49_9;
  TNode<JSAny> phi_bb49_11;
  TNode<FixedArray> phi_bb49_12;
  TNode<IntPtrT> phi_bb49_13;
  TNode<IntPtrT> phi_bb49_14;
  TNode<FixedArray> phi_bb49_18;
  TNode<IntPtrT> phi_bb49_19;
  TNode<IntPtrT> phi_bb49_20;
  TNode<UintPtrT> phi_bb49_22;
  TNode<Union<JSMessageObject, TheHole>> tmp81;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_9, &phi_bb49_11, &phi_bb49_12, &phi_bb49_13, &phi_bb49_14, &phi_bb49_18, &phi_bb49_19, &phi_bb49_20, &phi_bb49_22);
    tmp81 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb49_9, phi_bb49_11, phi_bb49_12, phi_bb49_13, phi_bb49_14, phi_bb49_18, phi_bb49_19, phi_bb49_20, phi_bb49_22, tmp73, tmp81);
  }

  TNode<Uint32T> phi_bb50_9;
  TNode<JSAny> phi_bb50_11;
  TNode<FixedArray> phi_bb50_12;
  TNode<IntPtrT> phi_bb50_13;
  TNode<IntPtrT> phi_bb50_14;
  TNode<FixedArray> phi_bb50_18;
  TNode<IntPtrT> phi_bb50_19;
  TNode<IntPtrT> phi_bb50_20;
  TNode<UintPtrT> phi_bb50_22;
  TNode<Union<JSMessageObject, TheHole>> tmp82;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_9, &phi_bb50_11, &phi_bb50_12, &phi_bb50_13, &phi_bb50_14, &phi_bb50_18, &phi_bb50_19, &phi_bb50_20, &phi_bb50_22);
    tmp82 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb50_9, phi_bb50_11, phi_bb50_12, phi_bb50_13, phi_bb50_14, phi_bb50_18, phi_bb50_19, phi_bb50_20, phi_bb50_22, tmp76, tmp82);
  }

  TNode<Uint32T> phi_bb53_9;
  TNode<JSAny> phi_bb53_11;
  TNode<FixedArray> phi_bb53_12;
  TNode<IntPtrT> phi_bb53_13;
  TNode<IntPtrT> phi_bb53_14;
  TNode<FixedArray> phi_bb53_18;
  TNode<IntPtrT> phi_bb53_19;
  TNode<IntPtrT> phi_bb53_20;
  TNode<UintPtrT> phi_bb53_22;
  TNode<Union<JSMessageObject, TheHole>> tmp83;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_9, &phi_bb53_11, &phi_bb53_12, &phi_bb53_13, &phi_bb53_14, &phi_bb53_18, &phi_bb53_19, &phi_bb53_20, &phi_bb53_22);
    tmp83 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb53_9, phi_bb53_11, phi_bb53_12, phi_bb53_13, phi_bb53_14, phi_bb53_18, phi_bb53_19, phi_bb53_20, phi_bb53_22, tmp80, tmp83);
  }

  TNode<Uint32T> phi_bb51_9;
  TNode<JSAny> phi_bb51_11;
  TNode<FixedArray> phi_bb51_12;
  TNode<IntPtrT> phi_bb51_13;
  TNode<IntPtrT> phi_bb51_14;
  TNode<FixedArray> phi_bb51_18;
  TNode<IntPtrT> phi_bb51_19;
  TNode<IntPtrT> phi_bb51_20;
  TNode<UintPtrT> phi_bb51_22;
  TNode<PropertyDescriptorObject> tmp84;
      TNode<JSAny> tmp87;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_9, &phi_bb51_11, &phi_bb51_12, &phi_bb51_13, &phi_bb51_14, &phi_bb51_18, &phi_bb51_19, &phi_bb51_20, &phi_bb51_22);
    compiler::CodeAssemblerLabel label85(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch86__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch86__label);
    tmp84 = Cast_PropertyDescriptorObject_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp74}, &label85);
    }
    if (catch86__label.is_used()) {
      compiler::CodeAssemblerLabel catch86_skip(&ca_);
      ca_.Goto(&catch86_skip);
      ca_.Bind(&catch86__label, &tmp87);
      ca_.Goto(&block58, phi_bb51_9, phi_bb51_11, phi_bb51_12, phi_bb51_13, phi_bb51_14, phi_bb51_18, phi_bb51_19, phi_bb51_20, phi_bb51_22);
      ca_.Bind(&catch86_skip);
    }
    ca_.Goto(&block56, phi_bb51_9, phi_bb51_11, phi_bb51_12, phi_bb51_13, phi_bb51_14, phi_bb51_18, phi_bb51_19, phi_bb51_20, phi_bb51_22);
    if (label85.is_used()) {
      ca_.Bind(&label85);
      ca_.Goto(&block57, phi_bb51_9, phi_bb51_11, phi_bb51_12, phi_bb51_13, phi_bb51_14, phi_bb51_18, phi_bb51_19, phi_bb51_20, phi_bb51_22);
    }
  }

  TNode<Uint32T> phi_bb58_9;
  TNode<JSAny> phi_bb58_11;
  TNode<FixedArray> phi_bb58_12;
  TNode<IntPtrT> phi_bb58_13;
  TNode<IntPtrT> phi_bb58_14;
  TNode<FixedArray> phi_bb58_18;
  TNode<IntPtrT> phi_bb58_19;
  TNode<IntPtrT> phi_bb58_20;
  TNode<UintPtrT> phi_bb58_22;
  TNode<Union<JSMessageObject, TheHole>> tmp88;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_9, &phi_bb58_11, &phi_bb58_12, &phi_bb58_13, &phi_bb58_14, &phi_bb58_18, &phi_bb58_19, &phi_bb58_20, &phi_bb58_22);
    tmp88 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb58_9, phi_bb58_11, phi_bb58_12, phi_bb58_13, phi_bb58_14, phi_bb58_18, phi_bb58_19, phi_bb58_20, phi_bb58_22, tmp87, tmp88);
  }

  TNode<Uint32T> phi_bb57_9;
  TNode<JSAny> phi_bb57_11;
  TNode<FixedArray> phi_bb57_12;
  TNode<IntPtrT> phi_bb57_13;
  TNode<IntPtrT> phi_bb57_14;
  TNode<FixedArray> phi_bb57_18;
  TNode<IntPtrT> phi_bb57_19;
  TNode<IntPtrT> phi_bb57_20;
  TNode<UintPtrT> phi_bb57_22;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_9, &phi_bb57_11, &phi_bb57_12, &phi_bb57_13, &phi_bb57_14, &phi_bb57_18, &phi_bb57_19, &phi_bb57_20, &phi_bb57_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:1963:60");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb56_9;
  TNode<JSAny> phi_bb56_11;
  TNode<FixedArray> phi_bb56_12;
  TNode<IntPtrT> phi_bb56_13;
  TNode<IntPtrT> phi_bb56_14;
  TNode<FixedArray> phi_bb56_18;
  TNode<IntPtrT> phi_bb56_19;
  TNode<IntPtrT> phi_bb56_20;
  TNode<UintPtrT> phi_bb56_22;
  TNode<IntPtrT> tmp89;
      TNode<JSAny> tmp91;
  TNode<Smi> tmp92;
  TNode<BoolT> tmp93;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_9, &phi_bb56_11, &phi_bb56_12, &phi_bb56_13, &phi_bb56_14, &phi_bb56_18, &phi_bb56_19, &phi_bb56_20, &phi_bb56_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch90__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch90__label);
    tmp89 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    }
    if (catch90__label.is_used()) {
      compiler::CodeAssemblerLabel catch90_skip(&ca_);
      ca_.Goto(&catch90_skip);
      ca_.Bind(&catch90__label, &tmp91);
      ca_.Goto(&block61, phi_bb56_9, phi_bb56_11, phi_bb56_12, phi_bb56_13, phi_bb56_14, phi_bb56_18, phi_bb56_19, phi_bb56_20, phi_bb56_22);
      ca_.Bind(&catch90_skip);
    }
    tmp92 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp84, tmp89});
    tmp93 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 2, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp92))));
    ca_.Branch(tmp93, &block62, std::vector<compiler::Node*>{phi_bb56_9, phi_bb56_11, phi_bb56_12, phi_bb56_13, phi_bb56_14, phi_bb56_18, phi_bb56_19, phi_bb56_20, phi_bb56_22}, &block63, std::vector<compiler::Node*>{phi_bb56_9, phi_bb56_11, phi_bb56_12, phi_bb56_13, phi_bb56_14, phi_bb56_18, phi_bb56_19, phi_bb56_20, phi_bb56_22});
  }

  TNode<Uint32T> phi_bb61_9;
  TNode<JSAny> phi_bb61_11;
  TNode<FixedArray> phi_bb61_12;
  TNode<IntPtrT> phi_bb61_13;
  TNode<IntPtrT> phi_bb61_14;
  TNode<FixedArray> phi_bb61_18;
  TNode<IntPtrT> phi_bb61_19;
  TNode<IntPtrT> phi_bb61_20;
  TNode<UintPtrT> phi_bb61_22;
  TNode<Union<JSMessageObject, TheHole>> tmp94;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_9, &phi_bb61_11, &phi_bb61_12, &phi_bb61_13, &phi_bb61_14, &phi_bb61_18, &phi_bb61_19, &phi_bb61_20, &phi_bb61_22);
    tmp94 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb61_9, phi_bb61_11, phi_bb61_12, phi_bb61_13, phi_bb61_14, phi_bb61_18, phi_bb61_19, phi_bb61_20, phi_bb61_22, tmp91, tmp94);
  }

  TNode<Uint32T> phi_bb62_9;
  TNode<JSAny> phi_bb62_11;
  TNode<FixedArray> phi_bb62_12;
  TNode<IntPtrT> phi_bb62_13;
  TNode<IntPtrT> phi_bb62_14;
  TNode<FixedArray> phi_bb62_18;
  TNode<IntPtrT> phi_bb62_19;
  TNode<IntPtrT> phi_bb62_20;
  TNode<UintPtrT> phi_bb62_22;
  TNode<IntPtrT> tmp95;
      TNode<JSAny> tmp97;
  TNode<Smi> tmp98;
  TNode<BoolT> tmp99;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_9, &phi_bb62_11, &phi_bb62_12, &phi_bb62_13, &phi_bb62_14, &phi_bb62_18, &phi_bb62_19, &phi_bb62_20, &phi_bb62_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch96__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch96__label);
    tmp95 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    }
    if (catch96__label.is_used()) {
      compiler::CodeAssemblerLabel catch96_skip(&ca_);
      ca_.Goto(&catch96_skip);
      ca_.Bind(&catch96__label, &tmp97);
      ca_.Goto(&block65, phi_bb62_9, phi_bb62_11, phi_bb62_12, phi_bb62_13, phi_bb62_14, phi_bb62_18, phi_bb62_19, phi_bb62_20, phi_bb62_22);
      ca_.Bind(&catch96_skip);
    }
    tmp98 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp84, tmp95});
    tmp99 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 1, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp98))));
    ca_.Goto(&block64, phi_bb62_9, phi_bb62_11, phi_bb62_12, phi_bb62_13, phi_bb62_14, phi_bb62_18, phi_bb62_19, phi_bb62_20, phi_bb62_22, tmp99);
  }

  TNode<Uint32T> phi_bb65_9;
  TNode<JSAny> phi_bb65_11;
  TNode<FixedArray> phi_bb65_12;
  TNode<IntPtrT> phi_bb65_13;
  TNode<IntPtrT> phi_bb65_14;
  TNode<FixedArray> phi_bb65_18;
  TNode<IntPtrT> phi_bb65_19;
  TNode<IntPtrT> phi_bb65_20;
  TNode<UintPtrT> phi_bb65_22;
  TNode<Union<JSMessageObject, TheHole>> tmp100;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_9, &phi_bb65_11, &phi_bb65_12, &phi_bb65_13, &phi_bb65_14, &phi_bb65_18, &phi_bb65_19, &phi_bb65_20, &phi_bb65_22);
    tmp100 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb65_9, phi_bb65_11, phi_bb65_12, phi_bb65_13, phi_bb65_14, phi_bb65_18, phi_bb65_19, phi_bb65_20, phi_bb65_22, tmp97, tmp100);
  }

  TNode<Uint32T> phi_bb63_9;
  TNode<JSAny> phi_bb63_11;
  TNode<FixedArray> phi_bb63_12;
  TNode<IntPtrT> phi_bb63_13;
  TNode<IntPtrT> phi_bb63_14;
  TNode<FixedArray> phi_bb63_18;
  TNode<IntPtrT> phi_bb63_19;
  TNode<IntPtrT> phi_bb63_20;
  TNode<UintPtrT> phi_bb63_22;
  TNode<BoolT> tmp101;
      TNode<JSAny> tmp103;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_9, &phi_bb63_11, &phi_bb63_12, &phi_bb63_13, &phi_bb63_14, &phi_bb63_18, &phi_bb63_19, &phi_bb63_20, &phi_bb63_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch102__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch102__label);
    tmp101 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    }
    if (catch102__label.is_used()) {
      compiler::CodeAssemblerLabel catch102_skip(&ca_);
      ca_.Goto(&catch102_skip);
      ca_.Bind(&catch102__label, &tmp103);
      ca_.Goto(&block66, phi_bb63_9, phi_bb63_11, phi_bb63_12, phi_bb63_13, phi_bb63_14, phi_bb63_18, phi_bb63_19, phi_bb63_20, phi_bb63_22);
      ca_.Bind(&catch102_skip);
    }
    ca_.Goto(&block64, phi_bb63_9, phi_bb63_11, phi_bb63_12, phi_bb63_13, phi_bb63_14, phi_bb63_18, phi_bb63_19, phi_bb63_20, phi_bb63_22, tmp101);
  }

  TNode<Uint32T> phi_bb66_9;
  TNode<JSAny> phi_bb66_11;
  TNode<FixedArray> phi_bb66_12;
  TNode<IntPtrT> phi_bb66_13;
  TNode<IntPtrT> phi_bb66_14;
  TNode<FixedArray> phi_bb66_18;
  TNode<IntPtrT> phi_bb66_19;
  TNode<IntPtrT> phi_bb66_20;
  TNode<UintPtrT> phi_bb66_22;
  TNode<Union<JSMessageObject, TheHole>> tmp104;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_9, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13, &phi_bb66_14, &phi_bb66_18, &phi_bb66_19, &phi_bb66_20, &phi_bb66_22);
    tmp104 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb66_9, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_18, phi_bb66_19, phi_bb66_20, phi_bb66_22, tmp103, tmp104);
  }

  TNode<Uint32T> phi_bb64_9;
  TNode<JSAny> phi_bb64_11;
  TNode<FixedArray> phi_bb64_12;
  TNode<IntPtrT> phi_bb64_13;
  TNode<IntPtrT> phi_bb64_14;
  TNode<FixedArray> phi_bb64_18;
  TNode<IntPtrT> phi_bb64_19;
  TNode<IntPtrT> phi_bb64_20;
  TNode<UintPtrT> phi_bb64_22;
  TNode<BoolT> phi_bb64_27;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_9, &phi_bb64_11, &phi_bb64_12, &phi_bb64_13, &phi_bb64_14, &phi_bb64_18, &phi_bb64_19, &phi_bb64_20, &phi_bb64_22, &phi_bb64_27);
    ca_.Branch(phi_bb64_27, &block59, std::vector<compiler::Node*>{phi_bb64_9, phi_bb64_11, phi_bb64_12, phi_bb64_13, phi_bb64_14, phi_bb64_18, phi_bb64_19, phi_bb64_20, phi_bb64_22}, &block60, std::vector<compiler::Node*>{phi_bb64_9, phi_bb64_11, phi_bb64_12, phi_bb64_13, phi_bb64_14, phi_bb64_18, phi_bb64_19, phi_bb64_20, phi_bb64_22});
  }

  TNode<Uint32T> phi_bb59_9;
  TNode<JSAny> phi_bb59_11;
  TNode<FixedArray> phi_bb59_12;
  TNode<IntPtrT> phi_bb59_13;
  TNode<IntPtrT> phi_bb59_14;
  TNode<FixedArray> phi_bb59_18;
  TNode<IntPtrT> phi_bb59_19;
  TNode<IntPtrT> phi_bb59_20;
  TNode<UintPtrT> phi_bb59_22;
  TNode<JSAny> tmp105;
      TNode<JSAny> tmp107;
  TNode<Undefined> tmp108;
  TNode<BoolT> tmp109;
      TNode<JSAny> tmp111;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_9, &phi_bb59_11, &phi_bb59_12, &phi_bb59_13, &phi_bb59_14, &phi_bb59_18, &phi_bb59_19, &phi_bb59_20, &phi_bb59_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch106__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch106__label);
    tmp105 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp2}, TNode<JSAny>{tmp69});
    }
    if (catch106__label.is_used()) {
      compiler::CodeAssemblerLabel catch106_skip(&ca_);
      ca_.Goto(&catch106_skip);
      ca_.Bind(&catch106__label, &tmp107);
      ca_.Goto(&block67, phi_bb59_9, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_18, phi_bb59_19, phi_bb59_20, phi_bb59_22);
      ca_.Bind(&catch106_skip);
    }
    tmp108 = Undefined_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch110__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch110__label);
    tmp109 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp105}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp108});
    }
    if (catch110__label.is_used()) {
      compiler::CodeAssemblerLabel catch110_skip(&ca_);
      ca_.Goto(&catch110_skip);
      ca_.Bind(&catch110__label, &tmp111);
      ca_.Goto(&block70, phi_bb59_9, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_18, phi_bb59_19, phi_bb59_20, phi_bb59_22);
      ca_.Bind(&catch110_skip);
    }
    ca_.Branch(tmp109, &block68, std::vector<compiler::Node*>{phi_bb59_9, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_18, phi_bb59_19, phi_bb59_20, phi_bb59_22}, &block69, std::vector<compiler::Node*>{phi_bb59_9, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_18, phi_bb59_19, phi_bb59_20, phi_bb59_22});
  }

  TNode<Uint32T> phi_bb67_9;
  TNode<JSAny> phi_bb67_11;
  TNode<FixedArray> phi_bb67_12;
  TNode<IntPtrT> phi_bb67_13;
  TNode<IntPtrT> phi_bb67_14;
  TNode<FixedArray> phi_bb67_18;
  TNode<IntPtrT> phi_bb67_19;
  TNode<IntPtrT> phi_bb67_20;
  TNode<UintPtrT> phi_bb67_22;
  TNode<Union<JSMessageObject, TheHole>> tmp112;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_9, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13, &phi_bb67_14, &phi_bb67_18, &phi_bb67_19, &phi_bb67_20, &phi_bb67_22);
    tmp112 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb67_9, phi_bb67_11, phi_bb67_12, phi_bb67_13, phi_bb67_14, phi_bb67_18, phi_bb67_19, phi_bb67_20, phi_bb67_22, tmp107, tmp112);
  }

  TNode<Uint32T> phi_bb70_9;
  TNode<JSAny> phi_bb70_11;
  TNode<FixedArray> phi_bb70_12;
  TNode<IntPtrT> phi_bb70_13;
  TNode<IntPtrT> phi_bb70_14;
  TNode<FixedArray> phi_bb70_18;
  TNode<IntPtrT> phi_bb70_19;
  TNode<IntPtrT> phi_bb70_20;
  TNode<UintPtrT> phi_bb70_22;
  TNode<Union<JSMessageObject, TheHole>> tmp113;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_9, &phi_bb70_11, &phi_bb70_12, &phi_bb70_13, &phi_bb70_14, &phi_bb70_18, &phi_bb70_19, &phi_bb70_20, &phi_bb70_22);
    tmp113 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb70_9, phi_bb70_11, phi_bb70_12, phi_bb70_13, phi_bb70_14, phi_bb70_18, phi_bb70_19, phi_bb70_20, phi_bb70_22, tmp111, tmp113);
  }

  TNode<Uint32T> phi_bb68_9;
  TNode<JSAny> phi_bb68_11;
  TNode<FixedArray> phi_bb68_12;
  TNode<IntPtrT> phi_bb68_13;
  TNode<IntPtrT> phi_bb68_14;
  TNode<FixedArray> phi_bb68_18;
  TNode<IntPtrT> phi_bb68_19;
  TNode<IntPtrT> phi_bb68_20;
  TNode<UintPtrT> phi_bb68_22;
  TNode<BoolT> tmp114;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_9, &phi_bb68_11, &phi_bb68_12, &phi_bb68_13, &phi_bb68_14, &phi_bb68_18, &phi_bb68_19, &phi_bb68_20, &phi_bb68_22);
    tmp114 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb68_20}, TNode<IntPtrT>{phi_bb68_19});
    ca_.Branch(tmp114, &block73, std::vector<compiler::Node*>{phi_bb68_9, phi_bb68_11, phi_bb68_12, phi_bb68_13, phi_bb68_14, phi_bb68_18, phi_bb68_19, phi_bb68_20, phi_bb68_22}, &block74, std::vector<compiler::Node*>{phi_bb68_9, phi_bb68_11, phi_bb68_12, phi_bb68_13, phi_bb68_14, phi_bb68_18, phi_bb68_19, phi_bb68_20, phi_bb68_22});
  }

  TNode<Uint32T> phi_bb74_9;
  TNode<JSAny> phi_bb74_11;
  TNode<FixedArray> phi_bb74_12;
  TNode<IntPtrT> phi_bb74_13;
  TNode<IntPtrT> phi_bb74_14;
  TNode<FixedArray> phi_bb74_18;
  TNode<IntPtrT> phi_bb74_19;
  TNode<IntPtrT> phi_bb74_20;
  TNode<UintPtrT> phi_bb74_22;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_9, &phi_bb74_11, &phi_bb74_12, &phi_bb74_13, &phi_bb74_14, &phi_bb74_18, &phi_bb74_19, &phi_bb74_20, &phi_bb74_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb73_9;
  TNode<JSAny> phi_bb73_11;
  TNode<FixedArray> phi_bb73_12;
  TNode<IntPtrT> phi_bb73_13;
  TNode<IntPtrT> phi_bb73_14;
  TNode<FixedArray> phi_bb73_18;
  TNode<IntPtrT> phi_bb73_19;
  TNode<IntPtrT> phi_bb73_20;
  TNode<UintPtrT> phi_bb73_22;
  TNode<BoolT> tmp115;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_9, &phi_bb73_11, &phi_bb73_12, &phi_bb73_13, &phi_bb73_14, &phi_bb73_18, &phi_bb73_19, &phi_bb73_20, &phi_bb73_22);
    tmp115 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb73_19}, TNode<IntPtrT>{phi_bb73_20});
    ca_.Branch(tmp115, &block75, std::vector<compiler::Node*>{phi_bb73_9, phi_bb73_11, phi_bb73_12, phi_bb73_13, phi_bb73_14, phi_bb73_18, phi_bb73_19, phi_bb73_20, phi_bb73_22}, &block76, std::vector<compiler::Node*>{phi_bb73_9, phi_bb73_11, phi_bb73_12, phi_bb73_13, phi_bb73_14, phi_bb73_18, phi_bb73_19, phi_bb73_20, phi_bb73_22});
  }

  TNode<Uint32T> phi_bb75_9;
  TNode<JSAny> phi_bb75_11;
  TNode<FixedArray> phi_bb75_12;
  TNode<IntPtrT> phi_bb75_13;
  TNode<IntPtrT> phi_bb75_14;
  TNode<FixedArray> phi_bb75_18;
  TNode<IntPtrT> phi_bb75_19;
  TNode<IntPtrT> phi_bb75_20;
  TNode<UintPtrT> phi_bb75_22;
  TNode<IntPtrT> tmp116;
  TNode<IntPtrT> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<IntPtrT> tmp119;
  TNode<IntPtrT> tmp120;
  TNode<IntPtrT> tmp121;
  TNode<BoolT> tmp122;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_9, &phi_bb75_11, &phi_bb75_12, &phi_bb75_13, &phi_bb75_14, &phi_bb75_18, &phi_bb75_19, &phi_bb75_20, &phi_bb75_22);
    tmp116 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp117 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb75_19}, TNode<IntPtrT>{tmp116});
    tmp118 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb75_19}, TNode<IntPtrT>{tmp117});
    tmp119 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp120 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp118}, TNode<IntPtrT>{tmp119});
    tmp121 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp122 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb75_20}, TNode<IntPtrT>{tmp121});
    ca_.Branch(tmp122, &block78, std::vector<compiler::Node*>{phi_bb75_9, phi_bb75_11, phi_bb75_12, phi_bb75_13, phi_bb75_14, phi_bb75_18, phi_bb75_20, phi_bb75_22}, &block79, std::vector<compiler::Node*>{phi_bb75_9, phi_bb75_11, phi_bb75_12, phi_bb75_13, phi_bb75_14, phi_bb75_18, phi_bb75_20, phi_bb75_22});
  }

  TNode<Uint32T> phi_bb79_9;
  TNode<JSAny> phi_bb79_11;
  TNode<FixedArray> phi_bb79_12;
  TNode<IntPtrT> phi_bb79_13;
  TNode<IntPtrT> phi_bb79_14;
  TNode<FixedArray> phi_bb79_18;
  TNode<IntPtrT> phi_bb79_20;
  TNode<UintPtrT> phi_bb79_22;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_9, &phi_bb79_11, &phi_bb79_12, &phi_bb79_13, &phi_bb79_14, &phi_bb79_18, &phi_bb79_20, &phi_bb79_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb78_9;
  TNode<JSAny> phi_bb78_11;
  TNode<FixedArray> phi_bb78_12;
  TNode<IntPtrT> phi_bb78_13;
  TNode<IntPtrT> phi_bb78_14;
  TNode<FixedArray> phi_bb78_18;
  TNode<IntPtrT> phi_bb78_20;
  TNode<UintPtrT> phi_bb78_22;
  TNode<IntPtrT> tmp123;
  TNode<BoolT> tmp124;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_9, &phi_bb78_11, &phi_bb78_12, &phi_bb78_13, &phi_bb78_14, &phi_bb78_18, &phi_bb78_20, &phi_bb78_22);
    tmp123 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp124 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp120}, TNode<IntPtrT>{tmp123});
    ca_.Branch(tmp124, &block80, std::vector<compiler::Node*>{phi_bb78_9, phi_bb78_11, phi_bb78_12, phi_bb78_13, phi_bb78_14, phi_bb78_18, phi_bb78_20, phi_bb78_22}, &block81, std::vector<compiler::Node*>{phi_bb78_9, phi_bb78_11, phi_bb78_12, phi_bb78_13, phi_bb78_14, phi_bb78_18, phi_bb78_20, phi_bb78_22});
  }

  TNode<Uint32T> phi_bb81_9;
  TNode<JSAny> phi_bb81_11;
  TNode<FixedArray> phi_bb81_12;
  TNode<IntPtrT> phi_bb81_13;
  TNode<IntPtrT> phi_bb81_14;
  TNode<FixedArray> phi_bb81_18;
  TNode<IntPtrT> phi_bb81_20;
  TNode<UintPtrT> phi_bb81_22;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_9, &phi_bb81_11, &phi_bb81_12, &phi_bb81_13, &phi_bb81_14, &phi_bb81_18, &phi_bb81_20, &phi_bb81_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb80_9;
  TNode<JSAny> phi_bb80_11;
  TNode<FixedArray> phi_bb80_12;
  TNode<IntPtrT> phi_bb80_13;
  TNode<IntPtrT> phi_bb80_14;
  TNode<FixedArray> phi_bb80_18;
  TNode<IntPtrT> phi_bb80_20;
  TNode<UintPtrT> phi_bb80_22;
  TNode<BoolT> tmp125;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_9, &phi_bb80_11, &phi_bb80_12, &phi_bb80_13, &phi_bb80_14, &phi_bb80_18, &phi_bb80_20, &phi_bb80_22);
    tmp125 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp120}, TNode<IntPtrT>{phi_bb80_20});
    ca_.Branch(tmp125, &block82, std::vector<compiler::Node*>{phi_bb80_9, phi_bb80_11, phi_bb80_12, phi_bb80_13, phi_bb80_14, phi_bb80_18, phi_bb80_20, phi_bb80_22}, &block83, std::vector<compiler::Node*>{phi_bb80_9, phi_bb80_11, phi_bb80_12, phi_bb80_13, phi_bb80_14, phi_bb80_18, phi_bb80_20, phi_bb80_22});
  }

  TNode<Uint32T> phi_bb83_9;
  TNode<JSAny> phi_bb83_11;
  TNode<FixedArray> phi_bb83_12;
  TNode<IntPtrT> phi_bb83_13;
  TNode<IntPtrT> phi_bb83_14;
  TNode<FixedArray> phi_bb83_18;
  TNode<IntPtrT> phi_bb83_20;
  TNode<UintPtrT> phi_bb83_22;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_9, &phi_bb83_11, &phi_bb83_12, &phi_bb83_13, &phi_bb83_14, &phi_bb83_18, &phi_bb83_20, &phi_bb83_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb82_9;
  TNode<JSAny> phi_bb82_11;
  TNode<FixedArray> phi_bb82_12;
  TNode<IntPtrT> phi_bb82_13;
  TNode<IntPtrT> phi_bb82_14;
  TNode<FixedArray> phi_bb82_18;
  TNode<IntPtrT> phi_bb82_20;
  TNode<UintPtrT> phi_bb82_22;
  TNode<IntPtrT> tmp126;
  TNode<TheHole> tmp127;
  TNode<FixedArray> tmp128;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_9, &phi_bb82_11, &phi_bb82_12, &phi_bb82_13, &phi_bb82_14, &phi_bb82_18, &phi_bb82_20, &phi_bb82_22);
    tmp126 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp127 = TheHole_0(state_);
    tmp128 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb82_18}, TNode<IntPtrT>{tmp126}, TNode<IntPtrT>{phi_bb82_20}, TNode<IntPtrT>{tmp120}, TNode<Hole>{tmp127});
    ca_.Goto(&block76, phi_bb82_9, phi_bb82_11, phi_bb82_12, phi_bb82_13, phi_bb82_14, tmp128, tmp120, phi_bb82_20, phi_bb82_22);
  }

  TNode<Uint32T> phi_bb76_9;
  TNode<JSAny> phi_bb76_11;
  TNode<FixedArray> phi_bb76_12;
  TNode<IntPtrT> phi_bb76_13;
  TNode<IntPtrT> phi_bb76_14;
  TNode<FixedArray> phi_bb76_18;
  TNode<IntPtrT> phi_bb76_19;
  TNode<IntPtrT> phi_bb76_20;
  TNode<UintPtrT> phi_bb76_22;
  TNode<Union<HeapObject, TaggedIndex>> tmp129;
  TNode<IntPtrT> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<IntPtrT> tmp132;
  TNode<IntPtrT> tmp133;
  TNode<UintPtrT> tmp134;
  TNode<UintPtrT> tmp135;
  TNode<BoolT> tmp136;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_9, &phi_bb76_11, &phi_bb76_12, &phi_bb76_13, &phi_bb76_14, &phi_bb76_18, &phi_bb76_19, &phi_bb76_20, &phi_bb76_22);
    std::tie(tmp129, tmp130, tmp131) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb76_18}).Flatten();
    tmp132 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp133 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb76_20}, TNode<IntPtrT>{tmp132});
    tmp134 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb76_20});
    tmp135 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp131});
    tmp136 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp134}, TNode<UintPtrT>{tmp135});
    ca_.Branch(tmp136, &block88, std::vector<compiler::Node*>{phi_bb76_9, phi_bb76_11, phi_bb76_12, phi_bb76_13, phi_bb76_14, phi_bb76_18, phi_bb76_19, phi_bb76_22, phi_bb76_18, phi_bb76_20, phi_bb76_20, phi_bb76_20, phi_bb76_20}, &block89, std::vector<compiler::Node*>{phi_bb76_9, phi_bb76_11, phi_bb76_12, phi_bb76_13, phi_bb76_14, phi_bb76_18, phi_bb76_19, phi_bb76_22, phi_bb76_18, phi_bb76_20, phi_bb76_20, phi_bb76_20, phi_bb76_20});
  }

  TNode<Uint32T> phi_bb88_9;
  TNode<JSAny> phi_bb88_11;
  TNode<FixedArray> phi_bb88_12;
  TNode<IntPtrT> phi_bb88_13;
  TNode<IntPtrT> phi_bb88_14;
  TNode<FixedArray> phi_bb88_18;
  TNode<IntPtrT> phi_bb88_19;
  TNode<UintPtrT> phi_bb88_22;
  TNode<FixedArray> phi_bb88_29;
  TNode<IntPtrT> phi_bb88_33;
  TNode<IntPtrT> phi_bb88_34;
  TNode<IntPtrT> phi_bb88_38;
  TNode<IntPtrT> phi_bb88_39;
  TNode<IntPtrT> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<Union<HeapObject, TaggedIndex>> tmp139;
  TNode<IntPtrT> tmp140;
  TNode<JSReceiver> tmp141;
      TNode<JSAny> tmp144;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_9, &phi_bb88_11, &phi_bb88_12, &phi_bb88_13, &phi_bb88_14, &phi_bb88_18, &phi_bb88_19, &phi_bb88_22, &phi_bb88_29, &phi_bb88_33, &phi_bb88_34, &phi_bb88_38, &phi_bb88_39);
    tmp137 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb88_39});
    tmp138 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp130}, TNode<IntPtrT>{tmp137});
    std::tie(tmp139, tmp140) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp129}, TNode<IntPtrT>{tmp138}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp139, tmp140}, tmp69);
    compiler::CodeAssemblerLabel label142(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch143__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch143__label);
    tmp141 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp105}, &label142);
    }
    if (catch143__label.is_used()) {
      compiler::CodeAssemblerLabel catch143_skip(&ca_);
      ca_.Goto(&catch143_skip);
      ca_.Bind(&catch143__label, &tmp144);
      ca_.Goto(&block96, phi_bb88_9, phi_bb88_11, phi_bb88_12, phi_bb88_13, phi_bb88_14, phi_bb88_18, phi_bb88_19, phi_bb88_22);
      ca_.Bind(&catch143_skip);
    }
    ca_.Goto(&block94, phi_bb88_9, phi_bb88_11, phi_bb88_12, phi_bb88_13, phi_bb88_14, phi_bb88_18, phi_bb88_19, phi_bb88_22);
    if (label142.is_used()) {
      ca_.Bind(&label142);
      ca_.Goto(&block95, phi_bb88_9, phi_bb88_11, phi_bb88_12, phi_bb88_13, phi_bb88_14, phi_bb88_18, phi_bb88_19, phi_bb88_22);
    }
  }

  TNode<Uint32T> phi_bb89_9;
  TNode<JSAny> phi_bb89_11;
  TNode<FixedArray> phi_bb89_12;
  TNode<IntPtrT> phi_bb89_13;
  TNode<IntPtrT> phi_bb89_14;
  TNode<FixedArray> phi_bb89_18;
  TNode<IntPtrT> phi_bb89_19;
  TNode<UintPtrT> phi_bb89_22;
  TNode<FixedArray> phi_bb89_29;
  TNode<IntPtrT> phi_bb89_33;
  TNode<IntPtrT> phi_bb89_34;
  TNode<IntPtrT> phi_bb89_38;
  TNode<IntPtrT> phi_bb89_39;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_9, &phi_bb89_11, &phi_bb89_12, &phi_bb89_13, &phi_bb89_14, &phi_bb89_18, &phi_bb89_19, &phi_bb89_22, &phi_bb89_29, &phi_bb89_33, &phi_bb89_34, &phi_bb89_38, &phi_bb89_39);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb96_9;
  TNode<JSAny> phi_bb96_11;
  TNode<FixedArray> phi_bb96_12;
  TNode<IntPtrT> phi_bb96_13;
  TNode<IntPtrT> phi_bb96_14;
  TNode<FixedArray> phi_bb96_18;
  TNode<IntPtrT> phi_bb96_19;
  TNode<UintPtrT> phi_bb96_22;
  TNode<Union<JSMessageObject, TheHole>> tmp145;
  if (block96.is_used()) {
    ca_.Bind(&block96, &phi_bb96_9, &phi_bb96_11, &phi_bb96_12, &phi_bb96_13, &phi_bb96_14, &phi_bb96_18, &phi_bb96_19, &phi_bb96_22);
    tmp145 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb96_9, phi_bb96_11, phi_bb96_12, phi_bb96_13, phi_bb96_14, phi_bb96_18, phi_bb96_19, tmp133, phi_bb96_22, tmp144, tmp145);
  }

  TNode<Uint32T> phi_bb95_9;
  TNode<JSAny> phi_bb95_11;
  TNode<FixedArray> phi_bb95_12;
  TNode<IntPtrT> phi_bb95_13;
  TNode<IntPtrT> phi_bb95_14;
  TNode<FixedArray> phi_bb95_18;
  TNode<IntPtrT> phi_bb95_19;
  TNode<UintPtrT> phi_bb95_22;
      TNode<JSAny> tmp147;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_9, &phi_bb95_11, &phi_bb95_12, &phi_bb95_13, &phi_bb95_14, &phi_bb95_18, &phi_bb95_19, &phi_bb95_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch146__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch146__label);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kNotIterable), TNode<Object>{tmp105});
    }
    if (catch146__label.is_used()) {
      compiler::CodeAssemblerLabel catch146_skip(&ca_);
      ca_.Bind(&catch146__label, &tmp147);
      ca_.Goto(&block97, phi_bb95_9, phi_bb95_11, phi_bb95_12, phi_bb95_13, phi_bb95_14, phi_bb95_18, phi_bb95_19, phi_bb95_22);
    }
  }

  TNode<Uint32T> phi_bb94_9;
  TNode<JSAny> phi_bb94_11;
  TNode<FixedArray> phi_bb94_12;
  TNode<IntPtrT> phi_bb94_13;
  TNode<IntPtrT> phi_bb94_14;
  TNode<FixedArray> phi_bb94_18;
  TNode<IntPtrT> phi_bb94_19;
  TNode<UintPtrT> phi_bb94_22;
  TNode<JSReceiver> tmp148;
  TNode<JSAny> tmp149;
      TNode<JSAny> tmp151;
  TNode<BoolT> tmp152;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_9, &phi_bb94_11, &phi_bb94_12, &phi_bb94_13, &phi_bb94_14, &phi_bb94_18, &phi_bb94_19, &phi_bb94_22);
    compiler::CodeAssemblerExceptionHandlerLabel catch150__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch150__label);
    std::tie(tmp148, tmp149) = GetIteratorFlattenable_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, String>>{tmp141}).Flatten();
    }
    if (catch150__label.is_used()) {
      compiler::CodeAssemblerLabel catch150_skip(&ca_);
      ca_.Goto(&catch150_skip);
      ca_.Bind(&catch150__label, &tmp151);
      ca_.Goto(&block98, phi_bb94_9, phi_bb94_11, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_18, phi_bb94_19, phi_bb94_22);
      ca_.Bind(&catch150_skip);
    }
    tmp152 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb94_14}, TNode<IntPtrT>{phi_bb94_13});
    ca_.Branch(tmp152, &block101, std::vector<compiler::Node*>{phi_bb94_9, phi_bb94_11, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_18, phi_bb94_19, phi_bb94_22}, &block102, std::vector<compiler::Node*>{phi_bb94_9, phi_bb94_11, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_18, phi_bb94_19, phi_bb94_22});
  }

  TNode<Uint32T> phi_bb97_9;
  TNode<JSAny> phi_bb97_11;
  TNode<FixedArray> phi_bb97_12;
  TNode<IntPtrT> phi_bb97_13;
  TNode<IntPtrT> phi_bb97_14;
  TNode<FixedArray> phi_bb97_18;
  TNode<IntPtrT> phi_bb97_19;
  TNode<UintPtrT> phi_bb97_22;
  TNode<Union<JSMessageObject, TheHole>> tmp153;
  if (block97.is_used()) {
    ca_.Bind(&block97, &phi_bb97_9, &phi_bb97_11, &phi_bb97_12, &phi_bb97_13, &phi_bb97_14, &phi_bb97_18, &phi_bb97_19, &phi_bb97_22);
    tmp153 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb97_9, phi_bb97_11, phi_bb97_12, phi_bb97_13, phi_bb97_14, phi_bb97_18, phi_bb97_19, tmp133, phi_bb97_22, tmp147, tmp153);
  }

  TNode<Uint32T> phi_bb98_9;
  TNode<JSAny> phi_bb98_11;
  TNode<FixedArray> phi_bb98_12;
  TNode<IntPtrT> phi_bb98_13;
  TNode<IntPtrT> phi_bb98_14;
  TNode<FixedArray> phi_bb98_18;
  TNode<IntPtrT> phi_bb98_19;
  TNode<UintPtrT> phi_bb98_22;
  TNode<Union<JSMessageObject, TheHole>> tmp154;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_9, &phi_bb98_11, &phi_bb98_12, &phi_bb98_13, &phi_bb98_14, &phi_bb98_18, &phi_bb98_19, &phi_bb98_22);
    tmp154 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block48, phi_bb98_9, phi_bb98_11, phi_bb98_12, phi_bb98_13, phi_bb98_14, phi_bb98_18, phi_bb98_19, tmp133, phi_bb98_22, tmp151, tmp154);
  }

  TNode<Uint32T> phi_bb102_9;
  TNode<JSAny> phi_bb102_11;
  TNode<FixedArray> phi_bb102_12;
  TNode<IntPtrT> phi_bb102_13;
  TNode<IntPtrT> phi_bb102_14;
  TNode<FixedArray> phi_bb102_18;
  TNode<IntPtrT> phi_bb102_19;
  TNode<UintPtrT> phi_bb102_22;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_9, &phi_bb102_11, &phi_bb102_12, &phi_bb102_13, &phi_bb102_14, &phi_bb102_18, &phi_bb102_19, &phi_bb102_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb101_9;
  TNode<JSAny> phi_bb101_11;
  TNode<FixedArray> phi_bb101_12;
  TNode<IntPtrT> phi_bb101_13;
  TNode<IntPtrT> phi_bb101_14;
  TNode<FixedArray> phi_bb101_18;
  TNode<IntPtrT> phi_bb101_19;
  TNode<UintPtrT> phi_bb101_22;
  TNode<BoolT> tmp155;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_9, &phi_bb101_11, &phi_bb101_12, &phi_bb101_13, &phi_bb101_14, &phi_bb101_18, &phi_bb101_19, &phi_bb101_22);
    tmp155 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb101_13}, TNode<IntPtrT>{phi_bb101_14});
    ca_.Branch(tmp155, &block103, std::vector<compiler::Node*>{phi_bb101_9, phi_bb101_11, phi_bb101_12, phi_bb101_13, phi_bb101_14, phi_bb101_18, phi_bb101_19, phi_bb101_22}, &block104, std::vector<compiler::Node*>{phi_bb101_9, phi_bb101_11, phi_bb101_12, phi_bb101_13, phi_bb101_14, phi_bb101_18, phi_bb101_19, phi_bb101_22});
  }

  TNode<Uint32T> phi_bb103_9;
  TNode<JSAny> phi_bb103_11;
  TNode<FixedArray> phi_bb103_12;
  TNode<IntPtrT> phi_bb103_13;
  TNode<IntPtrT> phi_bb103_14;
  TNode<FixedArray> phi_bb103_18;
  TNode<IntPtrT> phi_bb103_19;
  TNode<UintPtrT> phi_bb103_22;
  TNode<IntPtrT> tmp156;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<IntPtrT> tmp159;
  TNode<IntPtrT> tmp160;
  TNode<IntPtrT> tmp161;
  TNode<BoolT> tmp162;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_9, &phi_bb103_11, &phi_bb103_12, &phi_bb103_13, &phi_bb103_14, &phi_bb103_18, &phi_bb103_19, &phi_bb103_22);
    tmp156 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp157 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb103_13}, TNode<IntPtrT>{tmp156});
    tmp158 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb103_13}, TNode<IntPtrT>{tmp157});
    tmp159 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp160 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp158}, TNode<IntPtrT>{tmp159});
    tmp161 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp162 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb103_14}, TNode<IntPtrT>{tmp161});
    ca_.Branch(tmp162, &block106, std::vector<compiler::Node*>{phi_bb103_9, phi_bb103_11, phi_bb103_12, phi_bb103_14, phi_bb103_18, phi_bb103_19, phi_bb103_22}, &block107, std::vector<compiler::Node*>{phi_bb103_9, phi_bb103_11, phi_bb103_12, phi_bb103_14, phi_bb103_18, phi_bb103_19, phi_bb103_22});
  }

  TNode<Uint32T> phi_bb107_9;
  TNode<JSAny> phi_bb107_11;
  TNode<FixedArray> phi_bb107_12;
  TNode<IntPtrT> phi_bb107_14;
  TNode<FixedArray> phi_bb107_18;
  TNode<IntPtrT> phi_bb107_19;
  TNode<UintPtrT> phi_bb107_22;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_9, &phi_bb107_11, &phi_bb107_12, &phi_bb107_14, &phi_bb107_18, &phi_bb107_19, &phi_bb107_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb106_9;
  TNode<JSAny> phi_bb106_11;
  TNode<FixedArray> phi_bb106_12;
  TNode<IntPtrT> phi_bb106_14;
  TNode<FixedArray> phi_bb106_18;
  TNode<IntPtrT> phi_bb106_19;
  TNode<UintPtrT> phi_bb106_22;
  TNode<IntPtrT> tmp163;
  TNode<BoolT> tmp164;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_9, &phi_bb106_11, &phi_bb106_12, &phi_bb106_14, &phi_bb106_18, &phi_bb106_19, &phi_bb106_22);
    tmp163 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp164 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp160}, TNode<IntPtrT>{tmp163});
    ca_.Branch(tmp164, &block108, std::vector<compiler::Node*>{phi_bb106_9, phi_bb106_11, phi_bb106_12, phi_bb106_14, phi_bb106_18, phi_bb106_19, phi_bb106_22}, &block109, std::vector<compiler::Node*>{phi_bb106_9, phi_bb106_11, phi_bb106_12, phi_bb106_14, phi_bb106_18, phi_bb106_19, phi_bb106_22});
  }

  TNode<Uint32T> phi_bb109_9;
  TNode<JSAny> phi_bb109_11;
  TNode<FixedArray> phi_bb109_12;
  TNode<IntPtrT> phi_bb109_14;
  TNode<FixedArray> phi_bb109_18;
  TNode<IntPtrT> phi_bb109_19;
  TNode<UintPtrT> phi_bb109_22;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_9, &phi_bb109_11, &phi_bb109_12, &phi_bb109_14, &phi_bb109_18, &phi_bb109_19, &phi_bb109_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb108_9;
  TNode<JSAny> phi_bb108_11;
  TNode<FixedArray> phi_bb108_12;
  TNode<IntPtrT> phi_bb108_14;
  TNode<FixedArray> phi_bb108_18;
  TNode<IntPtrT> phi_bb108_19;
  TNode<UintPtrT> phi_bb108_22;
  TNode<BoolT> tmp165;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_9, &phi_bb108_11, &phi_bb108_12, &phi_bb108_14, &phi_bb108_18, &phi_bb108_19, &phi_bb108_22);
    tmp165 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp160}, TNode<IntPtrT>{phi_bb108_14});
    ca_.Branch(tmp165, &block110, std::vector<compiler::Node*>{phi_bb108_9, phi_bb108_11, phi_bb108_12, phi_bb108_14, phi_bb108_18, phi_bb108_19, phi_bb108_22}, &block111, std::vector<compiler::Node*>{phi_bb108_9, phi_bb108_11, phi_bb108_12, phi_bb108_14, phi_bb108_18, phi_bb108_19, phi_bb108_22});
  }

  TNode<Uint32T> phi_bb111_9;
  TNode<JSAny> phi_bb111_11;
  TNode<FixedArray> phi_bb111_12;
  TNode<IntPtrT> phi_bb111_14;
  TNode<FixedArray> phi_bb111_18;
  TNode<IntPtrT> phi_bb111_19;
  TNode<UintPtrT> phi_bb111_22;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_9, &phi_bb111_11, &phi_bb111_12, &phi_bb111_14, &phi_bb111_18, &phi_bb111_19, &phi_bb111_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb110_9;
  TNode<JSAny> phi_bb110_11;
  TNode<FixedArray> phi_bb110_12;
  TNode<IntPtrT> phi_bb110_14;
  TNode<FixedArray> phi_bb110_18;
  TNode<IntPtrT> phi_bb110_19;
  TNode<UintPtrT> phi_bb110_22;
  TNode<IntPtrT> tmp166;
  TNode<TheHole> tmp167;
  TNode<FixedArray> tmp168;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_9, &phi_bb110_11, &phi_bb110_12, &phi_bb110_14, &phi_bb110_18, &phi_bb110_19, &phi_bb110_22);
    tmp166 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp167 = TheHole_0(state_);
    tmp168 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb110_12}, TNode<IntPtrT>{tmp166}, TNode<IntPtrT>{phi_bb110_14}, TNode<IntPtrT>{tmp160}, TNode<Hole>{tmp167});
    ca_.Goto(&block104, phi_bb110_9, phi_bb110_11, tmp168, tmp160, phi_bb110_14, phi_bb110_18, phi_bb110_19, phi_bb110_22);
  }

  TNode<Uint32T> phi_bb104_9;
  TNode<JSAny> phi_bb104_11;
  TNode<FixedArray> phi_bb104_12;
  TNode<IntPtrT> phi_bb104_13;
  TNode<IntPtrT> phi_bb104_14;
  TNode<FixedArray> phi_bb104_18;
  TNode<IntPtrT> phi_bb104_19;
  TNode<UintPtrT> phi_bb104_22;
  TNode<Union<HeapObject, TaggedIndex>> tmp169;
  TNode<IntPtrT> tmp170;
  TNode<IntPtrT> tmp171;
  TNode<IntPtrT> tmp172;
  TNode<IntPtrT> tmp173;
  TNode<UintPtrT> tmp174;
  TNode<UintPtrT> tmp175;
  TNode<BoolT> tmp176;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_9, &phi_bb104_11, &phi_bb104_12, &phi_bb104_13, &phi_bb104_14, &phi_bb104_18, &phi_bb104_19, &phi_bb104_22);
    std::tie(tmp169, tmp170, tmp171) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb104_12}).Flatten();
    tmp172 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp173 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb104_14}, TNode<IntPtrT>{tmp172});
    tmp174 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb104_14});
    tmp175 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp171});
    tmp176 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp174}, TNode<UintPtrT>{tmp175});
    ca_.Branch(tmp176, &block116, std::vector<compiler::Node*>{phi_bb104_9, phi_bb104_11, phi_bb104_12, phi_bb104_13, phi_bb104_18, phi_bb104_19, phi_bb104_22, phi_bb104_12, phi_bb104_14, phi_bb104_14, phi_bb104_14, phi_bb104_14}, &block117, std::vector<compiler::Node*>{phi_bb104_9, phi_bb104_11, phi_bb104_12, phi_bb104_13, phi_bb104_18, phi_bb104_19, phi_bb104_22, phi_bb104_12, phi_bb104_14, phi_bb104_14, phi_bb104_14, phi_bb104_14});
  }

  TNode<Uint32T> phi_bb116_9;
  TNode<JSAny> phi_bb116_11;
  TNode<FixedArray> phi_bb116_12;
  TNode<IntPtrT> phi_bb116_13;
  TNode<FixedArray> phi_bb116_18;
  TNode<IntPtrT> phi_bb116_19;
  TNode<UintPtrT> phi_bb116_22;
  TNode<FixedArray> phi_bb116_32;
  TNode<IntPtrT> phi_bb116_36;
  TNode<IntPtrT> phi_bb116_37;
  TNode<IntPtrT> phi_bb116_41;
  TNode<IntPtrT> phi_bb116_42;
  TNode<IntPtrT> tmp177;
  TNode<IntPtrT> tmp178;
  TNode<Union<HeapObject, TaggedIndex>> tmp179;
  TNode<IntPtrT> tmp180;
  TNode<BoolT> tmp181;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_9, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13, &phi_bb116_18, &phi_bb116_19, &phi_bb116_22, &phi_bb116_32, &phi_bb116_36, &phi_bb116_37, &phi_bb116_41, &phi_bb116_42);
    tmp177 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb116_42});
    tmp178 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp170}, TNode<IntPtrT>{tmp177});
    std::tie(tmp179, tmp180) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp169}, TNode<IntPtrT>{tmp178}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp179, tmp180}, tmp148);
    tmp181 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp173}, TNode<IntPtrT>{phi_bb116_13});
    ca_.Branch(tmp181, &block122, std::vector<compiler::Node*>{phi_bb116_9, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_18, phi_bb116_19, phi_bb116_22}, &block123, std::vector<compiler::Node*>{phi_bb116_9, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_18, phi_bb116_19, phi_bb116_22});
  }

  TNode<Uint32T> phi_bb117_9;
  TNode<JSAny> phi_bb117_11;
  TNode<FixedArray> phi_bb117_12;
  TNode<IntPtrT> phi_bb117_13;
  TNode<FixedArray> phi_bb117_18;
  TNode<IntPtrT> phi_bb117_19;
  TNode<UintPtrT> phi_bb117_22;
  TNode<FixedArray> phi_bb117_32;
  TNode<IntPtrT> phi_bb117_36;
  TNode<IntPtrT> phi_bb117_37;
  TNode<IntPtrT> phi_bb117_41;
  TNode<IntPtrT> phi_bb117_42;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_9, &phi_bb117_11, &phi_bb117_12, &phi_bb117_13, &phi_bb117_18, &phi_bb117_19, &phi_bb117_22, &phi_bb117_32, &phi_bb117_36, &phi_bb117_37, &phi_bb117_41, &phi_bb117_42);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb123_9;
  TNode<JSAny> phi_bb123_11;
  TNode<FixedArray> phi_bb123_12;
  TNode<IntPtrT> phi_bb123_13;
  TNode<FixedArray> phi_bb123_18;
  TNode<IntPtrT> phi_bb123_19;
  TNode<UintPtrT> phi_bb123_22;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_9, &phi_bb123_11, &phi_bb123_12, &phi_bb123_13, &phi_bb123_18, &phi_bb123_19, &phi_bb123_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb122_9;
  TNode<JSAny> phi_bb122_11;
  TNode<FixedArray> phi_bb122_12;
  TNode<IntPtrT> phi_bb122_13;
  TNode<FixedArray> phi_bb122_18;
  TNode<IntPtrT> phi_bb122_19;
  TNode<UintPtrT> phi_bb122_22;
  TNode<BoolT> tmp182;
  if (block122.is_used()) {
    ca_.Bind(&block122, &phi_bb122_9, &phi_bb122_11, &phi_bb122_12, &phi_bb122_13, &phi_bb122_18, &phi_bb122_19, &phi_bb122_22);
    tmp182 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb122_13}, TNode<IntPtrT>{tmp173});
    ca_.Branch(tmp182, &block124, std::vector<compiler::Node*>{phi_bb122_9, phi_bb122_11, phi_bb122_12, phi_bb122_13, phi_bb122_18, phi_bb122_19, phi_bb122_22}, &block125, std::vector<compiler::Node*>{phi_bb122_9, phi_bb122_11, phi_bb122_12, phi_bb122_13, phi_bb122_18, phi_bb122_19, phi_bb122_22});
  }

  TNode<Uint32T> phi_bb124_9;
  TNode<JSAny> phi_bb124_11;
  TNode<FixedArray> phi_bb124_12;
  TNode<IntPtrT> phi_bb124_13;
  TNode<FixedArray> phi_bb124_18;
  TNode<IntPtrT> phi_bb124_19;
  TNode<UintPtrT> phi_bb124_22;
  TNode<IntPtrT> tmp183;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<IntPtrT> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<IntPtrT> tmp188;
  TNode<BoolT> tmp189;
  if (block124.is_used()) {
    ca_.Bind(&block124, &phi_bb124_9, &phi_bb124_11, &phi_bb124_12, &phi_bb124_13, &phi_bb124_18, &phi_bb124_19, &phi_bb124_22);
    tmp183 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp184 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb124_13}, TNode<IntPtrT>{tmp183});
    tmp185 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb124_13}, TNode<IntPtrT>{tmp184});
    tmp186 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp187 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp185}, TNode<IntPtrT>{tmp186});
    tmp188 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp189 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp173}, TNode<IntPtrT>{tmp188});
    ca_.Branch(tmp189, &block127, std::vector<compiler::Node*>{phi_bb124_9, phi_bb124_11, phi_bb124_12, phi_bb124_18, phi_bb124_19, phi_bb124_22}, &block128, std::vector<compiler::Node*>{phi_bb124_9, phi_bb124_11, phi_bb124_12, phi_bb124_18, phi_bb124_19, phi_bb124_22});
  }

  TNode<Uint32T> phi_bb128_9;
  TNode<JSAny> phi_bb128_11;
  TNode<FixedArray> phi_bb128_12;
  TNode<FixedArray> phi_bb128_18;
  TNode<IntPtrT> phi_bb128_19;
  TNode<UintPtrT> phi_bb128_22;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_9, &phi_bb128_11, &phi_bb128_12, &phi_bb128_18, &phi_bb128_19, &phi_bb128_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb127_9;
  TNode<JSAny> phi_bb127_11;
  TNode<FixedArray> phi_bb127_12;
  TNode<FixedArray> phi_bb127_18;
  TNode<IntPtrT> phi_bb127_19;
  TNode<UintPtrT> phi_bb127_22;
  TNode<IntPtrT> tmp190;
  TNode<BoolT> tmp191;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_9, &phi_bb127_11, &phi_bb127_12, &phi_bb127_18, &phi_bb127_19, &phi_bb127_22);
    tmp190 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp191 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp187}, TNode<IntPtrT>{tmp190});
    ca_.Branch(tmp191, &block129, std::vector<compiler::Node*>{phi_bb127_9, phi_bb127_11, phi_bb127_12, phi_bb127_18, phi_bb127_19, phi_bb127_22}, &block130, std::vector<compiler::Node*>{phi_bb127_9, phi_bb127_11, phi_bb127_12, phi_bb127_18, phi_bb127_19, phi_bb127_22});
  }

  TNode<Uint32T> phi_bb130_9;
  TNode<JSAny> phi_bb130_11;
  TNode<FixedArray> phi_bb130_12;
  TNode<FixedArray> phi_bb130_18;
  TNode<IntPtrT> phi_bb130_19;
  TNode<UintPtrT> phi_bb130_22;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_9, &phi_bb130_11, &phi_bb130_12, &phi_bb130_18, &phi_bb130_19, &phi_bb130_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb129_9;
  TNode<JSAny> phi_bb129_11;
  TNode<FixedArray> phi_bb129_12;
  TNode<FixedArray> phi_bb129_18;
  TNode<IntPtrT> phi_bb129_19;
  TNode<UintPtrT> phi_bb129_22;
  TNode<BoolT> tmp192;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_9, &phi_bb129_11, &phi_bb129_12, &phi_bb129_18, &phi_bb129_19, &phi_bb129_22);
    tmp192 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp187}, TNode<IntPtrT>{tmp173});
    ca_.Branch(tmp192, &block131, std::vector<compiler::Node*>{phi_bb129_9, phi_bb129_11, phi_bb129_12, phi_bb129_18, phi_bb129_19, phi_bb129_22}, &block132, std::vector<compiler::Node*>{phi_bb129_9, phi_bb129_11, phi_bb129_12, phi_bb129_18, phi_bb129_19, phi_bb129_22});
  }

  TNode<Uint32T> phi_bb132_9;
  TNode<JSAny> phi_bb132_11;
  TNode<FixedArray> phi_bb132_12;
  TNode<FixedArray> phi_bb132_18;
  TNode<IntPtrT> phi_bb132_19;
  TNode<UintPtrT> phi_bb132_22;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_9, &phi_bb132_11, &phi_bb132_12, &phi_bb132_18, &phi_bb132_19, &phi_bb132_22);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb131_9;
  TNode<JSAny> phi_bb131_11;
  TNode<FixedArray> phi_bb131_12;
  TNode<FixedArray> phi_bb131_18;
  TNode<IntPtrT> phi_bb131_19;
  TNode<UintPtrT> phi_bb131_22;
  TNode<IntPtrT> tmp193;
  TNode<TheHole> tmp194;
  TNode<FixedArray> tmp195;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_9, &phi_bb131_11, &phi_bb131_12, &phi_bb131_18, &phi_bb131_19, &phi_bb131_22);
    tmp193 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp194 = TheHole_0(state_);
    tmp195 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb131_12}, TNode<IntPtrT>{tmp193}, TNode<IntPtrT>{tmp173}, TNode<IntPtrT>{tmp187}, TNode<Hole>{tmp194});
    ca_.Goto(&block125, phi_bb131_9, phi_bb131_11, tmp195, tmp187, phi_bb131_18, phi_bb131_19, phi_bb131_22);
  }

  TNode<Uint32T> phi_bb125_9;
  TNode<JSAny> phi_bb125_11;
  TNode<FixedArray> phi_bb125_12;
  TNode<IntPtrT> phi_bb125_13;
  TNode<FixedArray> phi_bb125_18;
  TNode<IntPtrT> phi_bb125_19;
  TNode<UintPtrT> phi_bb125_22;
  TNode<Union<HeapObject, TaggedIndex>> tmp196;
  TNode<IntPtrT> tmp197;
  TNode<IntPtrT> tmp198;
  TNode<IntPtrT> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<UintPtrT> tmp201;
  TNode<UintPtrT> tmp202;
  TNode<BoolT> tmp203;
  if (block125.is_used()) {
    ca_.Bind(&block125, &phi_bb125_9, &phi_bb125_11, &phi_bb125_12, &phi_bb125_13, &phi_bb125_18, &phi_bb125_19, &phi_bb125_22);
    std::tie(tmp196, tmp197, tmp198) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb125_12}).Flatten();
    tmp199 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp200 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp173}, TNode<IntPtrT>{tmp199});
    tmp201 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp173});
    tmp202 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp198});
    tmp203 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp201}, TNode<UintPtrT>{tmp202});
    ca_.Branch(tmp203, &block137, std::vector<compiler::Node*>{phi_bb125_9, phi_bb125_11, phi_bb125_12, phi_bb125_13, phi_bb125_18, phi_bb125_19, phi_bb125_22, phi_bb125_12}, &block138, std::vector<compiler::Node*>{phi_bb125_9, phi_bb125_11, phi_bb125_12, phi_bb125_13, phi_bb125_18, phi_bb125_19, phi_bb125_22, phi_bb125_12});
  }

  TNode<Uint32T> phi_bb137_9;
  TNode<JSAny> phi_bb137_11;
  TNode<FixedArray> phi_bb137_12;
  TNode<IntPtrT> phi_bb137_13;
  TNode<FixedArray> phi_bb137_18;
  TNode<IntPtrT> phi_bb137_19;
  TNode<UintPtrT> phi_bb137_22;
  TNode<FixedArray> phi_bb137_32;
  TNode<IntPtrT> tmp204;
  TNode<IntPtrT> tmp205;
  TNode<Union<HeapObject, TaggedIndex>> tmp206;
  TNode<IntPtrT> tmp207;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_9, &phi_bb137_11, &phi_bb137_12, &phi_bb137_13, &phi_bb137_18, &phi_bb137_19, &phi_bb137_22, &phi_bb137_32);
    tmp204 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp173});
    tmp205 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp197}, TNode<IntPtrT>{tmp204});
    std::tie(tmp206, tmp207) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp196}, TNode<IntPtrT>{tmp205}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp206, tmp207}, tmp149);
    ca_.Goto(&block69, phi_bb137_9, phi_bb137_11, phi_bb137_12, phi_bb137_13, tmp200, phi_bb137_18, phi_bb137_19, tmp133, phi_bb137_22);
  }

  TNode<Uint32T> phi_bb138_9;
  TNode<JSAny> phi_bb138_11;
  TNode<FixedArray> phi_bb138_12;
  TNode<IntPtrT> phi_bb138_13;
  TNode<FixedArray> phi_bb138_18;
  TNode<IntPtrT> phi_bb138_19;
  TNode<UintPtrT> phi_bb138_22;
  TNode<FixedArray> phi_bb138_32;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_9, &phi_bb138_11, &phi_bb138_12, &phi_bb138_13, &phi_bb138_18, &phi_bb138_19, &phi_bb138_22, &phi_bb138_32);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb69_9;
  TNode<JSAny> phi_bb69_11;
  TNode<FixedArray> phi_bb69_12;
  TNode<IntPtrT> phi_bb69_13;
  TNode<IntPtrT> phi_bb69_14;
  TNode<FixedArray> phi_bb69_18;
  TNode<IntPtrT> phi_bb69_19;
  TNode<IntPtrT> phi_bb69_20;
  TNode<UintPtrT> phi_bb69_22;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_9, &phi_bb69_11, &phi_bb69_12, &phi_bb69_13, &phi_bb69_14, &phi_bb69_18, &phi_bb69_19, &phi_bb69_20, &phi_bb69_22);
    ca_.Goto(&block60, phi_bb69_9, phi_bb69_11, phi_bb69_12, phi_bb69_13, phi_bb69_14, phi_bb69_18, phi_bb69_19, phi_bb69_20, phi_bb69_22);
  }

  TNode<Uint32T> phi_bb60_9;
  TNode<JSAny> phi_bb60_11;
  TNode<FixedArray> phi_bb60_12;
  TNode<IntPtrT> phi_bb60_13;
  TNode<IntPtrT> phi_bb60_14;
  TNode<FixedArray> phi_bb60_18;
  TNode<IntPtrT> phi_bb60_19;
  TNode<IntPtrT> phi_bb60_20;
  TNode<UintPtrT> phi_bb60_22;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_9, &phi_bb60_11, &phi_bb60_12, &phi_bb60_13, &phi_bb60_14, &phi_bb60_18, &phi_bb60_19, &phi_bb60_20, &phi_bb60_22);
    ca_.Goto(&block52, phi_bb60_9, phi_bb60_11, phi_bb60_12, phi_bb60_13, phi_bb60_14, phi_bb60_18, phi_bb60_19, phi_bb60_20, phi_bb60_22);
  }

  TNode<Uint32T> phi_bb52_9;
  TNode<JSAny> phi_bb52_11;
  TNode<FixedArray> phi_bb52_12;
  TNode<IntPtrT> phi_bb52_13;
  TNode<IntPtrT> phi_bb52_14;
  TNode<FixedArray> phi_bb52_18;
  TNode<IntPtrT> phi_bb52_19;
  TNode<IntPtrT> phi_bb52_20;
  TNode<UintPtrT> phi_bb52_22;
  TNode<UintPtrT> tmp208;
  TNode<UintPtrT> tmp209;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_9, &phi_bb52_11, &phi_bb52_12, &phi_bb52_13, &phi_bb52_14, &phi_bb52_18, &phi_bb52_19, &phi_bb52_20, &phi_bb52_22);
    tmp208 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp209 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb52_22}, TNode<UintPtrT>{tmp208});
    ca_.Goto(&block33, phi_bb52_9, phi_bb52_11, phi_bb52_12, phi_bb52_13, phi_bb52_14, phi_bb52_18, phi_bb52_19, phi_bb52_20, tmp209);
  }

  TNode<Uint32T> phi_bb48_9;
  TNode<JSAny> phi_bb48_11;
  TNode<FixedArray> phi_bb48_12;
  TNode<IntPtrT> phi_bb48_13;
  TNode<IntPtrT> phi_bb48_14;
  TNode<FixedArray> phi_bb48_18;
  TNode<IntPtrT> phi_bb48_19;
  TNode<IntPtrT> phi_bb48_20;
  TNode<UintPtrT> phi_bb48_22;
  TNode<JSAny> phi_bb48_24;
  TNode<Union<JSMessageObject, TheHole>> phi_bb48_25;
  TNode<IntPtrT> tmp210;
  TNode<BoolT> tmp211;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_9, &phi_bb48_11, &phi_bb48_12, &phi_bb48_13, &phi_bb48_14, &phi_bb48_18, &phi_bb48_19, &phi_bb48_20, &phi_bb48_22, &phi_bb48_24, &phi_bb48_25);
    tmp210 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp211 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb48_14}, TNode<IntPtrT>{tmp210});
    ca_.Branch(tmp211, &block142, std::vector<compiler::Node*>{phi_bb48_9, phi_bb48_11, phi_bb48_12, phi_bb48_13, phi_bb48_14, phi_bb48_18, phi_bb48_19, phi_bb48_20, phi_bb48_22, phi_bb48_14, phi_bb48_14}, &block143, std::vector<compiler::Node*>{phi_bb48_9, phi_bb48_11, phi_bb48_12, phi_bb48_13, phi_bb48_14, phi_bb48_18, phi_bb48_19, phi_bb48_20, phi_bb48_22, phi_bb48_14, phi_bb48_14});
  }

  TNode<Uint32T> phi_bb143_9;
  TNode<JSAny> phi_bb143_11;
  TNode<FixedArray> phi_bb143_12;
  TNode<IntPtrT> phi_bb143_13;
  TNode<IntPtrT> phi_bb143_14;
  TNode<FixedArray> phi_bb143_18;
  TNode<IntPtrT> phi_bb143_19;
  TNode<IntPtrT> phi_bb143_20;
  TNode<UintPtrT> phi_bb143_22;
  TNode<IntPtrT> phi_bb143_26;
  TNode<IntPtrT> phi_bb143_27;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_9, &phi_bb143_11, &phi_bb143_12, &phi_bb143_13, &phi_bb143_14, &phi_bb143_18, &phi_bb143_19, &phi_bb143_20, &phi_bb143_22, &phi_bb143_26, &phi_bb143_27);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb142_9;
  TNode<JSAny> phi_bb142_11;
  TNode<FixedArray> phi_bb142_12;
  TNode<IntPtrT> phi_bb142_13;
  TNode<IntPtrT> phi_bb142_14;
  TNode<FixedArray> phi_bb142_18;
  TNode<IntPtrT> phi_bb142_19;
  TNode<IntPtrT> phi_bb142_20;
  TNode<UintPtrT> phi_bb142_22;
  TNode<IntPtrT> phi_bb142_26;
  TNode<IntPtrT> phi_bb142_27;
  TNode<IntPtrT> tmp212;
  TNode<BoolT> tmp213;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_9, &phi_bb142_11, &phi_bb142_12, &phi_bb142_13, &phi_bb142_14, &phi_bb142_18, &phi_bb142_19, &phi_bb142_20, &phi_bb142_22, &phi_bb142_26, &phi_bb142_27);
    tmp212 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp213 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb142_27}, TNode<IntPtrT>{tmp212});
    ca_.Branch(tmp213, &block144, std::vector<compiler::Node*>{phi_bb142_9, phi_bb142_11, phi_bb142_12, phi_bb142_13, phi_bb142_14, phi_bb142_18, phi_bb142_19, phi_bb142_20, phi_bb142_22, phi_bb142_26, phi_bb142_27}, &block145, std::vector<compiler::Node*>{phi_bb142_9, phi_bb142_11, phi_bb142_12, phi_bb142_13, phi_bb142_14, phi_bb142_18, phi_bb142_19, phi_bb142_20, phi_bb142_22, phi_bb142_26, phi_bb142_27});
  }

  TNode<Uint32T> phi_bb145_9;
  TNode<JSAny> phi_bb145_11;
  TNode<FixedArray> phi_bb145_12;
  TNode<IntPtrT> phi_bb145_13;
  TNode<IntPtrT> phi_bb145_14;
  TNode<FixedArray> phi_bb145_18;
  TNode<IntPtrT> phi_bb145_19;
  TNode<IntPtrT> phi_bb145_20;
  TNode<UintPtrT> phi_bb145_22;
  TNode<IntPtrT> phi_bb145_26;
  TNode<IntPtrT> phi_bb145_27;
  if (block145.is_used()) {
    ca_.Bind(&block145, &phi_bb145_9, &phi_bb145_11, &phi_bb145_12, &phi_bb145_13, &phi_bb145_14, &phi_bb145_18, &phi_bb145_19, &phi_bb145_20, &phi_bb145_22, &phi_bb145_26, &phi_bb145_27);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb144_9;
  TNode<JSAny> phi_bb144_11;
  TNode<FixedArray> phi_bb144_12;
  TNode<IntPtrT> phi_bb144_13;
  TNode<IntPtrT> phi_bb144_14;
  TNode<FixedArray> phi_bb144_18;
  TNode<IntPtrT> phi_bb144_19;
  TNode<IntPtrT> phi_bb144_20;
  TNode<UintPtrT> phi_bb144_22;
  TNode<IntPtrT> phi_bb144_26;
  TNode<IntPtrT> phi_bb144_27;
  TNode<BoolT> tmp214;
  if (block144.is_used()) {
    ca_.Bind(&block144, &phi_bb144_9, &phi_bb144_11, &phi_bb144_12, &phi_bb144_13, &phi_bb144_14, &phi_bb144_18, &phi_bb144_19, &phi_bb144_20, &phi_bb144_22, &phi_bb144_26, &phi_bb144_27);
    tmp214 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb144_27}, TNode<IntPtrT>{phi_bb144_14});
    ca_.Branch(tmp214, &block146, std::vector<compiler::Node*>{phi_bb144_9, phi_bb144_11, phi_bb144_12, phi_bb144_13, phi_bb144_14, phi_bb144_18, phi_bb144_19, phi_bb144_20, phi_bb144_22, phi_bb144_26, phi_bb144_27}, &block147, std::vector<compiler::Node*>{phi_bb144_9, phi_bb144_11, phi_bb144_12, phi_bb144_13, phi_bb144_14, phi_bb144_18, phi_bb144_19, phi_bb144_20, phi_bb144_22, phi_bb144_26, phi_bb144_27});
  }

  TNode<Uint32T> phi_bb147_9;
  TNode<JSAny> phi_bb147_11;
  TNode<FixedArray> phi_bb147_12;
  TNode<IntPtrT> phi_bb147_13;
  TNode<IntPtrT> phi_bb147_14;
  TNode<FixedArray> phi_bb147_18;
  TNode<IntPtrT> phi_bb147_19;
  TNode<IntPtrT> phi_bb147_20;
  TNode<UintPtrT> phi_bb147_22;
  TNode<IntPtrT> phi_bb147_26;
  TNode<IntPtrT> phi_bb147_27;
  if (block147.is_used()) {
    ca_.Bind(&block147, &phi_bb147_9, &phi_bb147_11, &phi_bb147_12, &phi_bb147_13, &phi_bb147_14, &phi_bb147_18, &phi_bb147_19, &phi_bb147_20, &phi_bb147_22, &phi_bb147_26, &phi_bb147_27);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb146_9;
  TNode<JSAny> phi_bb146_11;
  TNode<FixedArray> phi_bb146_12;
  TNode<IntPtrT> phi_bb146_13;
  TNode<IntPtrT> phi_bb146_14;
  TNode<FixedArray> phi_bb146_18;
  TNode<IntPtrT> phi_bb146_19;
  TNode<IntPtrT> phi_bb146_20;
  TNode<UintPtrT> phi_bb146_22;
  TNode<IntPtrT> phi_bb146_26;
  TNode<IntPtrT> phi_bb146_27;
  TNode<IntPtrT> tmp215;
  TNode<TheHole> tmp216;
  TNode<FixedArray> tmp217;
  if (block146.is_used()) {
    ca_.Bind(&block146, &phi_bb146_9, &phi_bb146_11, &phi_bb146_12, &phi_bb146_13, &phi_bb146_14, &phi_bb146_18, &phi_bb146_19, &phi_bb146_20, &phi_bb146_22, &phi_bb146_26, &phi_bb146_27);
    tmp215 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp216 = TheHole_0(state_);
    tmp217 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb146_12}, TNode<IntPtrT>{tmp215}, TNode<IntPtrT>{phi_bb146_14}, TNode<IntPtrT>{phi_bb146_27}, TNode<Hole>{tmp216});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp217}, false);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb48_24, phi_bb48_25);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb32_9;
  TNode<JSAny> phi_bb32_11;
  TNode<FixedArray> phi_bb32_12;
  TNode<IntPtrT> phi_bb32_13;
  TNode<IntPtrT> phi_bb32_14;
  TNode<FixedArray> phi_bb32_18;
  TNode<IntPtrT> phi_bb32_19;
  TNode<IntPtrT> phi_bb32_20;
  TNode<UintPtrT> phi_bb32_22;
  TNode<IntPtrT> tmp218;
  TNode<IntPtrT> tmp219;
  TNode<Uint32T> tmp220;
  TNode<BoolT> tmp221;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_9, &phi_bb32_11, &phi_bb32_12, &phi_bb32_13, &phi_bb32_14, &phi_bb32_18, &phi_bb32_19, &phi_bb32_20, &phi_bb32_22);
    tmp218 = FromConstexpr_intptr_constexpr_int31_0(state_, kIteratorRecordFieldCount_0(state_));
    tmp219 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{phi_bb32_14}, TNode<IntPtrT>{tmp218});
    tmp220 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(JSIteratorZipHelperMode::kLongest));
    tmp221 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{phi_bb32_9}, TNode<Uint32T>{tmp220});
    ca_.Branch(tmp221, &block148, std::vector<compiler::Node*>{phi_bb32_9, phi_bb32_11, phi_bb32_12, phi_bb32_13, phi_bb32_14, phi_bb32_18, phi_bb32_19, phi_bb32_20}, &block149, std::vector<compiler::Node*>{phi_bb32_9, phi_bb32_11, phi_bb32_12, phi_bb32_13, phi_bb32_14, tmp42, phi_bb32_18, phi_bb32_19, phi_bb32_20});
  }

  TNode<Uint32T> phi_bb148_9;
  TNode<JSAny> phi_bb148_11;
  TNode<FixedArray> phi_bb148_12;
  TNode<IntPtrT> phi_bb148_13;
  TNode<IntPtrT> phi_bb148_14;
  TNode<FixedArray> phi_bb148_18;
  TNode<IntPtrT> phi_bb148_19;
  TNode<IntPtrT> phi_bb148_20;
  TNode<Undefined> tmp222;
  TNode<Undefined> tmp223;
  TNode<FixedArray> tmp224;
  TNode<Undefined> tmp225;
  TNode<BoolT> tmp226;
  if (block148.is_used()) {
    ca_.Bind(&block148, &phi_bb148_9, &phi_bb148_11, &phi_bb148_12, &phi_bb148_13, &phi_bb148_14, &phi_bb148_18, &phi_bb148_19, &phi_bb148_20);
    tmp222 = Undefined_0(state_);
    std::tie(tmp223) = ConstantIterator_Undefined_0(state_, TNode<Undefined>{tmp222}).Flatten();
    tmp224 = NewFixedArray_ConstantIterator_Undefined_0(state_, TNode<IntPtrT>{tmp219}, TorqueStructConstantIterator_Undefined_0{TNode<Undefined>{tmp223}});
    tmp225 = Undefined_0(state_);
    tmp226 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{phi_bb148_11}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp225});
    ca_.Branch(tmp226, &block150, std::vector<compiler::Node*>{phi_bb148_9, phi_bb148_11, phi_bb148_12, phi_bb148_13, phi_bb148_14, phi_bb148_18, phi_bb148_19, phi_bb148_20}, &block151, std::vector<compiler::Node*>{phi_bb148_9, phi_bb148_11, phi_bb148_12, phi_bb148_13, phi_bb148_14, phi_bb148_18, phi_bb148_19, phi_bb148_20});
  }

  TNode<Uint32T> phi_bb150_9;
  TNode<JSAny> phi_bb150_11;
  TNode<FixedArray> phi_bb150_12;
  TNode<IntPtrT> phi_bb150_13;
  TNode<IntPtrT> phi_bb150_14;
  TNode<FixedArray> phi_bb150_18;
  TNode<IntPtrT> phi_bb150_19;
  TNode<IntPtrT> phi_bb150_20;
  TNode<IntPtrT> tmp227;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_9, &phi_bb150_11, &phi_bb150_12, &phi_bb150_13, &phi_bb150_14, &phi_bb150_18, &phi_bb150_19, &phi_bb150_20);
    tmp227 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block154, phi_bb150_9, phi_bb150_11, phi_bb150_12, phi_bb150_13, phi_bb150_14, phi_bb150_18, phi_bb150_19, phi_bb150_20, phi_bb150_18, tmp227);
  }

  TNode<Uint32T> phi_bb154_9;
  TNode<JSAny> phi_bb154_11;
  TNode<FixedArray> phi_bb154_12;
  TNode<IntPtrT> phi_bb154_13;
  TNode<IntPtrT> phi_bb154_14;
  TNode<FixedArray> phi_bb154_18;
  TNode<IntPtrT> phi_bb154_19;
  TNode<IntPtrT> phi_bb154_20;
  TNode<FixedArray> phi_bb154_23;
  TNode<IntPtrT> phi_bb154_24;
  TNode<BoolT> tmp228;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_9, &phi_bb154_11, &phi_bb154_12, &phi_bb154_13, &phi_bb154_14, &phi_bb154_18, &phi_bb154_19, &phi_bb154_20, &phi_bb154_23, &phi_bb154_24);
    tmp228 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb154_24}, TNode<IntPtrT>{tmp219});
    ca_.Branch(tmp228, &block152, std::vector<compiler::Node*>{phi_bb154_9, phi_bb154_11, phi_bb154_12, phi_bb154_13, phi_bb154_14, phi_bb154_18, phi_bb154_19, phi_bb154_20, phi_bb154_23, phi_bb154_24}, &block153, std::vector<compiler::Node*>{phi_bb154_9, phi_bb154_11, phi_bb154_12, phi_bb154_13, phi_bb154_14, phi_bb154_18, phi_bb154_19, phi_bb154_20, phi_bb154_23, phi_bb154_24});
  }

  TNode<Uint32T> phi_bb152_9;
  TNode<JSAny> phi_bb152_11;
  TNode<FixedArray> phi_bb152_12;
  TNode<IntPtrT> phi_bb152_13;
  TNode<IntPtrT> phi_bb152_14;
  TNode<FixedArray> phi_bb152_18;
  TNode<IntPtrT> phi_bb152_19;
  TNode<IntPtrT> phi_bb152_20;
  TNode<FixedArray> phi_bb152_23;
  TNode<IntPtrT> phi_bb152_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp229;
  TNode<IntPtrT> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<UintPtrT> tmp232;
  TNode<UintPtrT> tmp233;
  TNode<BoolT> tmp234;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_9, &phi_bb152_11, &phi_bb152_12, &phi_bb152_13, &phi_bb152_14, &phi_bb152_18, &phi_bb152_19, &phi_bb152_20, &phi_bb152_23, &phi_bb152_24);
    std::tie(tmp229, tmp230, tmp231) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb152_23}).Flatten();
    tmp232 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb152_24});
    tmp233 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp231});
    tmp234 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp232}, TNode<UintPtrT>{tmp233});
    ca_.Branch(tmp234, &block162, std::vector<compiler::Node*>{phi_bb152_9, phi_bb152_11, phi_bb152_12, phi_bb152_13, phi_bb152_14, phi_bb152_18, phi_bb152_19, phi_bb152_20, phi_bb152_23, phi_bb152_24, phi_bb152_23, phi_bb152_24, phi_bb152_24, phi_bb152_24, phi_bb152_24}, &block163, std::vector<compiler::Node*>{phi_bb152_9, phi_bb152_11, phi_bb152_12, phi_bb152_13, phi_bb152_14, phi_bb152_18, phi_bb152_19, phi_bb152_20, phi_bb152_23, phi_bb152_24, phi_bb152_23, phi_bb152_24, phi_bb152_24, phi_bb152_24, phi_bb152_24});
  }

  TNode<Uint32T> phi_bb162_9;
  TNode<JSAny> phi_bb162_11;
  TNode<FixedArray> phi_bb162_12;
  TNode<IntPtrT> phi_bb162_13;
  TNode<IntPtrT> phi_bb162_14;
  TNode<FixedArray> phi_bb162_18;
  TNode<IntPtrT> phi_bb162_19;
  TNode<IntPtrT> phi_bb162_20;
  TNode<FixedArray> phi_bb162_23;
  TNode<IntPtrT> phi_bb162_24;
  TNode<FixedArray> phi_bb162_25;
  TNode<IntPtrT> phi_bb162_29;
  TNode<IntPtrT> phi_bb162_30;
  TNode<IntPtrT> phi_bb162_34;
  TNode<IntPtrT> phi_bb162_35;
  TNode<IntPtrT> tmp235;
  TNode<IntPtrT> tmp236;
  TNode<Union<HeapObject, TaggedIndex>> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<Object> tmp239;
  TNode<JSAny> tmp240;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_9, &phi_bb162_11, &phi_bb162_12, &phi_bb162_13, &phi_bb162_14, &phi_bb162_18, &phi_bb162_19, &phi_bb162_20, &phi_bb162_23, &phi_bb162_24, &phi_bb162_25, &phi_bb162_29, &phi_bb162_30, &phi_bb162_34, &phi_bb162_35);
    tmp235 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb162_35});
    tmp236 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp230}, TNode<IntPtrT>{tmp235});
    std::tie(tmp237, tmp238) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp229}, TNode<IntPtrT>{tmp236}).Flatten();
    tmp239 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp237, tmp238});
    compiler::CodeAssemblerLabel label241(&ca_);
    tmp240 = Cast_JSAny_0(state_, TNode<Object>{tmp239}, &label241);
    ca_.Goto(&block166, phi_bb162_9, phi_bb162_11, phi_bb162_12, phi_bb162_13, phi_bb162_14, phi_bb162_18, phi_bb162_19, phi_bb162_20, phi_bb162_23, phi_bb162_24);
    if (label241.is_used()) {
      ca_.Bind(&label241);
      ca_.Goto(&block167, phi_bb162_9, phi_bb162_11, phi_bb162_12, phi_bb162_13, phi_bb162_14, phi_bb162_18, phi_bb162_19, phi_bb162_20, phi_bb162_23, phi_bb162_24);
    }
  }

  TNode<Uint32T> phi_bb163_9;
  TNode<JSAny> phi_bb163_11;
  TNode<FixedArray> phi_bb163_12;
  TNode<IntPtrT> phi_bb163_13;
  TNode<IntPtrT> phi_bb163_14;
  TNode<FixedArray> phi_bb163_18;
  TNode<IntPtrT> phi_bb163_19;
  TNode<IntPtrT> phi_bb163_20;
  TNode<FixedArray> phi_bb163_23;
  TNode<IntPtrT> phi_bb163_24;
  TNode<FixedArray> phi_bb163_25;
  TNode<IntPtrT> phi_bb163_29;
  TNode<IntPtrT> phi_bb163_30;
  TNode<IntPtrT> phi_bb163_34;
  TNode<IntPtrT> phi_bb163_35;
  if (block163.is_used()) {
    ca_.Bind(&block163, &phi_bb163_9, &phi_bb163_11, &phi_bb163_12, &phi_bb163_13, &phi_bb163_14, &phi_bb163_18, &phi_bb163_19, &phi_bb163_20, &phi_bb163_23, &phi_bb163_24, &phi_bb163_25, &phi_bb163_29, &phi_bb163_30, &phi_bb163_34, &phi_bb163_35);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb167_9;
  TNode<JSAny> phi_bb167_11;
  TNode<FixedArray> phi_bb167_12;
  TNode<IntPtrT> phi_bb167_13;
  TNode<IntPtrT> phi_bb167_14;
  TNode<FixedArray> phi_bb167_18;
  TNode<IntPtrT> phi_bb167_19;
  TNode<IntPtrT> phi_bb167_20;
  TNode<FixedArray> phi_bb167_23;
  TNode<IntPtrT> phi_bb167_24;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_9, &phi_bb167_11, &phi_bb167_12, &phi_bb167_13, &phi_bb167_14, &phi_bb167_18, &phi_bb167_19, &phi_bb167_20, &phi_bb167_23, &phi_bb167_24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:2007:65");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb166_9;
  TNode<JSAny> phi_bb166_11;
  TNode<FixedArray> phi_bb166_12;
  TNode<IntPtrT> phi_bb166_13;
  TNode<IntPtrT> phi_bb166_14;
  TNode<FixedArray> phi_bb166_18;
  TNode<IntPtrT> phi_bb166_19;
  TNode<IntPtrT> phi_bb166_20;
  TNode<FixedArray> phi_bb166_23;
  TNode<IntPtrT> phi_bb166_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp242;
  TNode<IntPtrT> tmp243;
  TNode<IntPtrT> tmp244;
      TNode<JSAny> tmp246;
  TNode<UintPtrT> tmp247;
  TNode<UintPtrT> tmp248;
  TNode<BoolT> tmp249;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_9, &phi_bb166_11, &phi_bb166_12, &phi_bb166_13, &phi_bb166_14, &phi_bb166_18, &phi_bb166_19, &phi_bb166_20, &phi_bb166_23, &phi_bb166_24);
    compiler::CodeAssemblerExceptionHandlerLabel catch245__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch245__label);
    std::tie(tmp242, tmp243, tmp244) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp224}).Flatten();
    }
    if (catch245__label.is_used()) {
      compiler::CodeAssemblerLabel catch245_skip(&ca_);
      ca_.Goto(&catch245_skip);
      ca_.Bind(&catch245__label, &tmp246);
      ca_.Goto(&block170, phi_bb166_9, phi_bb166_11, phi_bb166_12, phi_bb166_13, phi_bb166_14, phi_bb166_18, phi_bb166_19, phi_bb166_20, phi_bb166_23, phi_bb166_24);
      ca_.Bind(&catch245_skip);
    }
    tmp247 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb166_24});
    tmp248 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp244});
    tmp249 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp247}, TNode<UintPtrT>{tmp248});
    ca_.Branch(tmp249, &block175, std::vector<compiler::Node*>{phi_bb166_9, phi_bb166_11, phi_bb166_12, phi_bb166_13, phi_bb166_14, phi_bb166_18, phi_bb166_19, phi_bb166_20, phi_bb166_23, phi_bb166_24, phi_bb166_24, phi_bb166_24, phi_bb166_24, phi_bb166_24}, &block176, std::vector<compiler::Node*>{phi_bb166_9, phi_bb166_11, phi_bb166_12, phi_bb166_13, phi_bb166_14, phi_bb166_18, phi_bb166_19, phi_bb166_20, phi_bb166_23, phi_bb166_24, phi_bb166_24, phi_bb166_24, phi_bb166_24, phi_bb166_24});
  }

  TNode<Uint32T> phi_bb170_9;
  TNode<JSAny> phi_bb170_11;
  TNode<FixedArray> phi_bb170_12;
  TNode<IntPtrT> phi_bb170_13;
  TNode<IntPtrT> phi_bb170_14;
  TNode<FixedArray> phi_bb170_18;
  TNode<IntPtrT> phi_bb170_19;
  TNode<IntPtrT> phi_bb170_20;
  TNode<FixedArray> phi_bb170_23;
  TNode<IntPtrT> phi_bb170_24;
  TNode<Union<JSMessageObject, TheHole>> tmp250;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_9, &phi_bb170_11, &phi_bb170_12, &phi_bb170_13, &phi_bb170_14, &phi_bb170_18, &phi_bb170_19, &phi_bb170_20, &phi_bb170_23, &phi_bb170_24);
    tmp250 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block169, phi_bb170_9, phi_bb170_11, phi_bb170_12, phi_bb170_13, phi_bb170_14, phi_bb170_18, phi_bb170_19, phi_bb170_20, phi_bb170_23, phi_bb170_24, tmp246, tmp250);
  }

  TNode<Uint32T> phi_bb175_9;
  TNode<JSAny> phi_bb175_11;
  TNode<FixedArray> phi_bb175_12;
  TNode<IntPtrT> phi_bb175_13;
  TNode<IntPtrT> phi_bb175_14;
  TNode<FixedArray> phi_bb175_18;
  TNode<IntPtrT> phi_bb175_19;
  TNode<IntPtrT> phi_bb175_20;
  TNode<FixedArray> phi_bb175_23;
  TNode<IntPtrT> phi_bb175_24;
  TNode<IntPtrT> phi_bb175_30;
  TNode<IntPtrT> phi_bb175_31;
  TNode<IntPtrT> phi_bb175_35;
  TNode<IntPtrT> phi_bb175_36;
  TNode<IntPtrT> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<Union<HeapObject, TaggedIndex>> tmp253;
  TNode<IntPtrT> tmp254;
  TNode<JSAny> tmp255;
      TNode<JSAny> tmp257;
  TNode<IntPtrT> tmp258;
  TNode<IntPtrT> tmp259;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_9, &phi_bb175_11, &phi_bb175_12, &phi_bb175_13, &phi_bb175_14, &phi_bb175_18, &phi_bb175_19, &phi_bb175_20, &phi_bb175_23, &phi_bb175_24, &phi_bb175_30, &phi_bb175_31, &phi_bb175_35, &phi_bb175_36);
    tmp251 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb175_36});
    tmp252 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp243}, TNode<IntPtrT>{tmp251});
    std::tie(tmp253, tmp254) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp242}, TNode<IntPtrT>{tmp252}).Flatten();
    compiler::CodeAssemblerExceptionHandlerLabel catch256__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch256__label);
    tmp255 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{phi_bb175_11}, TNode<JSAny>{tmp240});
    }
    if (catch256__label.is_used()) {
      compiler::CodeAssemblerLabel catch256_skip(&ca_);
      ca_.Goto(&catch256_skip);
      ca_.Bind(&catch256__label, &tmp257);
      ca_.Goto(&block179, phi_bb175_9, phi_bb175_11, phi_bb175_12, phi_bb175_13, phi_bb175_14, phi_bb175_18, phi_bb175_19, phi_bb175_20, phi_bb175_23, phi_bb175_24, phi_bb175_30, phi_bb175_31, phi_bb175_11);
      ca_.Bind(&catch256_skip);
    }
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp253, tmp254}, tmp255);
    tmp258 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp259 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb175_24}, TNode<IntPtrT>{tmp258});
    ca_.Goto(&block154, phi_bb175_9, phi_bb175_11, phi_bb175_12, phi_bb175_13, phi_bb175_14, phi_bb175_18, phi_bb175_19, phi_bb175_20, phi_bb175_23, tmp259);
  }

  TNode<Uint32T> phi_bb176_9;
  TNode<JSAny> phi_bb176_11;
  TNode<FixedArray> phi_bb176_12;
  TNode<IntPtrT> phi_bb176_13;
  TNode<IntPtrT> phi_bb176_14;
  TNode<FixedArray> phi_bb176_18;
  TNode<IntPtrT> phi_bb176_19;
  TNode<IntPtrT> phi_bb176_20;
  TNode<FixedArray> phi_bb176_23;
  TNode<IntPtrT> phi_bb176_24;
  TNode<IntPtrT> phi_bb176_30;
  TNode<IntPtrT> phi_bb176_31;
  TNode<IntPtrT> phi_bb176_35;
  TNode<IntPtrT> phi_bb176_36;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_9, &phi_bb176_11, &phi_bb176_12, &phi_bb176_13, &phi_bb176_14, &phi_bb176_18, &phi_bb176_19, &phi_bb176_20, &phi_bb176_23, &phi_bb176_24, &phi_bb176_30, &phi_bb176_31, &phi_bb176_35, &phi_bb176_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb179_9;
  TNode<JSAny> phi_bb179_11;
  TNode<FixedArray> phi_bb179_12;
  TNode<IntPtrT> phi_bb179_13;
  TNode<IntPtrT> phi_bb179_14;
  TNode<FixedArray> phi_bb179_18;
  TNode<IntPtrT> phi_bb179_19;
  TNode<IntPtrT> phi_bb179_20;
  TNode<FixedArray> phi_bb179_23;
  TNode<IntPtrT> phi_bb179_24;
  TNode<IntPtrT> phi_bb179_30;
  TNode<IntPtrT> phi_bb179_31;
  TNode<JSAny> phi_bb179_34;
  TNode<Union<JSMessageObject, TheHole>> tmp260;
  if (block179.is_used()) {
    ca_.Bind(&block179, &phi_bb179_9, &phi_bb179_11, &phi_bb179_12, &phi_bb179_13, &phi_bb179_14, &phi_bb179_18, &phi_bb179_19, &phi_bb179_20, &phi_bb179_23, &phi_bb179_24, &phi_bb179_30, &phi_bb179_31, &phi_bb179_34);
    tmp260 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block169, phi_bb179_9, phi_bb179_11, phi_bb179_12, phi_bb179_13, phi_bb179_14, phi_bb179_18, phi_bb179_19, phi_bb179_20, phi_bb179_23, phi_bb179_24, tmp257, tmp260);
  }

  TNode<Uint32T> phi_bb169_9;
  TNode<JSAny> phi_bb169_11;
  TNode<FixedArray> phi_bb169_12;
  TNode<IntPtrT> phi_bb169_13;
  TNode<IntPtrT> phi_bb169_14;
  TNode<FixedArray> phi_bb169_18;
  TNode<IntPtrT> phi_bb169_19;
  TNode<IntPtrT> phi_bb169_20;
  TNode<FixedArray> phi_bb169_23;
  TNode<IntPtrT> phi_bb169_24;
  TNode<JSAny> phi_bb169_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb169_27;
  TNode<IntPtrT> tmp261;
  TNode<BoolT> tmp262;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_9, &phi_bb169_11, &phi_bb169_12, &phi_bb169_13, &phi_bb169_14, &phi_bb169_18, &phi_bb169_19, &phi_bb169_20, &phi_bb169_23, &phi_bb169_24, &phi_bb169_26, &phi_bb169_27);
    tmp261 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp262 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb169_14}, TNode<IntPtrT>{tmp261});
    ca_.Branch(tmp262, &block181, std::vector<compiler::Node*>{phi_bb169_9, phi_bb169_11, phi_bb169_12, phi_bb169_13, phi_bb169_14, phi_bb169_18, phi_bb169_19, phi_bb169_20, phi_bb169_23, phi_bb169_24, phi_bb169_26, phi_bb169_27, phi_bb169_14, phi_bb169_14}, &block182, std::vector<compiler::Node*>{phi_bb169_9, phi_bb169_11, phi_bb169_12, phi_bb169_13, phi_bb169_14, phi_bb169_18, phi_bb169_19, phi_bb169_20, phi_bb169_23, phi_bb169_24, phi_bb169_26, phi_bb169_27, phi_bb169_14, phi_bb169_14});
  }

  TNode<Uint32T> phi_bb182_9;
  TNode<JSAny> phi_bb182_11;
  TNode<FixedArray> phi_bb182_12;
  TNode<IntPtrT> phi_bb182_13;
  TNode<IntPtrT> phi_bb182_14;
  TNode<FixedArray> phi_bb182_18;
  TNode<IntPtrT> phi_bb182_19;
  TNode<IntPtrT> phi_bb182_20;
  TNode<FixedArray> phi_bb182_23;
  TNode<IntPtrT> phi_bb182_24;
  TNode<JSAny> phi_bb182_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb182_27;
  TNode<IntPtrT> phi_bb182_28;
  TNode<IntPtrT> phi_bb182_29;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_9, &phi_bb182_11, &phi_bb182_12, &phi_bb182_13, &phi_bb182_14, &phi_bb182_18, &phi_bb182_19, &phi_bb182_20, &phi_bb182_23, &phi_bb182_24, &phi_bb182_26, &phi_bb182_27, &phi_bb182_28, &phi_bb182_29);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb181_9;
  TNode<JSAny> phi_bb181_11;
  TNode<FixedArray> phi_bb181_12;
  TNode<IntPtrT> phi_bb181_13;
  TNode<IntPtrT> phi_bb181_14;
  TNode<FixedArray> phi_bb181_18;
  TNode<IntPtrT> phi_bb181_19;
  TNode<IntPtrT> phi_bb181_20;
  TNode<FixedArray> phi_bb181_23;
  TNode<IntPtrT> phi_bb181_24;
  TNode<JSAny> phi_bb181_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb181_27;
  TNode<IntPtrT> phi_bb181_28;
  TNode<IntPtrT> phi_bb181_29;
  TNode<IntPtrT> tmp263;
  TNode<BoolT> tmp264;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_9, &phi_bb181_11, &phi_bb181_12, &phi_bb181_13, &phi_bb181_14, &phi_bb181_18, &phi_bb181_19, &phi_bb181_20, &phi_bb181_23, &phi_bb181_24, &phi_bb181_26, &phi_bb181_27, &phi_bb181_28, &phi_bb181_29);
    tmp263 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp264 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb181_29}, TNode<IntPtrT>{tmp263});
    ca_.Branch(tmp264, &block183, std::vector<compiler::Node*>{phi_bb181_9, phi_bb181_11, phi_bb181_12, phi_bb181_13, phi_bb181_14, phi_bb181_18, phi_bb181_19, phi_bb181_20, phi_bb181_23, phi_bb181_24, phi_bb181_26, phi_bb181_27, phi_bb181_28, phi_bb181_29}, &block184, std::vector<compiler::Node*>{phi_bb181_9, phi_bb181_11, phi_bb181_12, phi_bb181_13, phi_bb181_14, phi_bb181_18, phi_bb181_19, phi_bb181_20, phi_bb181_23, phi_bb181_24, phi_bb181_26, phi_bb181_27, phi_bb181_28, phi_bb181_29});
  }

  TNode<Uint32T> phi_bb184_9;
  TNode<JSAny> phi_bb184_11;
  TNode<FixedArray> phi_bb184_12;
  TNode<IntPtrT> phi_bb184_13;
  TNode<IntPtrT> phi_bb184_14;
  TNode<FixedArray> phi_bb184_18;
  TNode<IntPtrT> phi_bb184_19;
  TNode<IntPtrT> phi_bb184_20;
  TNode<FixedArray> phi_bb184_23;
  TNode<IntPtrT> phi_bb184_24;
  TNode<JSAny> phi_bb184_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb184_27;
  TNode<IntPtrT> phi_bb184_28;
  TNode<IntPtrT> phi_bb184_29;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_9, &phi_bb184_11, &phi_bb184_12, &phi_bb184_13, &phi_bb184_14, &phi_bb184_18, &phi_bb184_19, &phi_bb184_20, &phi_bb184_23, &phi_bb184_24, &phi_bb184_26, &phi_bb184_27, &phi_bb184_28, &phi_bb184_29);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb183_9;
  TNode<JSAny> phi_bb183_11;
  TNode<FixedArray> phi_bb183_12;
  TNode<IntPtrT> phi_bb183_13;
  TNode<IntPtrT> phi_bb183_14;
  TNode<FixedArray> phi_bb183_18;
  TNode<IntPtrT> phi_bb183_19;
  TNode<IntPtrT> phi_bb183_20;
  TNode<FixedArray> phi_bb183_23;
  TNode<IntPtrT> phi_bb183_24;
  TNode<JSAny> phi_bb183_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb183_27;
  TNode<IntPtrT> phi_bb183_28;
  TNode<IntPtrT> phi_bb183_29;
  TNode<BoolT> tmp265;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_9, &phi_bb183_11, &phi_bb183_12, &phi_bb183_13, &phi_bb183_14, &phi_bb183_18, &phi_bb183_19, &phi_bb183_20, &phi_bb183_23, &phi_bb183_24, &phi_bb183_26, &phi_bb183_27, &phi_bb183_28, &phi_bb183_29);
    tmp265 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb183_29}, TNode<IntPtrT>{phi_bb183_14});
    ca_.Branch(tmp265, &block185, std::vector<compiler::Node*>{phi_bb183_9, phi_bb183_11, phi_bb183_12, phi_bb183_13, phi_bb183_14, phi_bb183_18, phi_bb183_19, phi_bb183_20, phi_bb183_23, phi_bb183_24, phi_bb183_26, phi_bb183_27, phi_bb183_28, phi_bb183_29}, &block186, std::vector<compiler::Node*>{phi_bb183_9, phi_bb183_11, phi_bb183_12, phi_bb183_13, phi_bb183_14, phi_bb183_18, phi_bb183_19, phi_bb183_20, phi_bb183_23, phi_bb183_24, phi_bb183_26, phi_bb183_27, phi_bb183_28, phi_bb183_29});
  }

  TNode<Uint32T> phi_bb186_9;
  TNode<JSAny> phi_bb186_11;
  TNode<FixedArray> phi_bb186_12;
  TNode<IntPtrT> phi_bb186_13;
  TNode<IntPtrT> phi_bb186_14;
  TNode<FixedArray> phi_bb186_18;
  TNode<IntPtrT> phi_bb186_19;
  TNode<IntPtrT> phi_bb186_20;
  TNode<FixedArray> phi_bb186_23;
  TNode<IntPtrT> phi_bb186_24;
  TNode<JSAny> phi_bb186_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb186_27;
  TNode<IntPtrT> phi_bb186_28;
  TNode<IntPtrT> phi_bb186_29;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_9, &phi_bb186_11, &phi_bb186_12, &phi_bb186_13, &phi_bb186_14, &phi_bb186_18, &phi_bb186_19, &phi_bb186_20, &phi_bb186_23, &phi_bb186_24, &phi_bb186_26, &phi_bb186_27, &phi_bb186_28, &phi_bb186_29);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb185_9;
  TNode<JSAny> phi_bb185_11;
  TNode<FixedArray> phi_bb185_12;
  TNode<IntPtrT> phi_bb185_13;
  TNode<IntPtrT> phi_bb185_14;
  TNode<FixedArray> phi_bb185_18;
  TNode<IntPtrT> phi_bb185_19;
  TNode<IntPtrT> phi_bb185_20;
  TNode<FixedArray> phi_bb185_23;
  TNode<IntPtrT> phi_bb185_24;
  TNode<JSAny> phi_bb185_26;
  TNode<Union<JSMessageObject, TheHole>> phi_bb185_27;
  TNode<IntPtrT> phi_bb185_28;
  TNode<IntPtrT> phi_bb185_29;
  TNode<IntPtrT> tmp266;
  TNode<TheHole> tmp267;
  TNode<FixedArray> tmp268;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_9, &phi_bb185_11, &phi_bb185_12, &phi_bb185_13, &phi_bb185_14, &phi_bb185_18, &phi_bb185_19, &phi_bb185_20, &phi_bb185_23, &phi_bb185_24, &phi_bb185_26, &phi_bb185_27, &phi_bb185_28, &phi_bb185_29);
    tmp266 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp267 = TheHole_0(state_);
    tmp268 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb185_12}, TNode<IntPtrT>{tmp266}, TNode<IntPtrT>{phi_bb185_14}, TNode<IntPtrT>{phi_bb185_29}, TNode<Hole>{tmp267});
    IteratorZipCloseAll_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp268}, false);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb185_26, phi_bb185_27);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Uint32T> phi_bb153_9;
  TNode<JSAny> phi_bb153_11;
  TNode<FixedArray> phi_bb153_12;
  TNode<IntPtrT> phi_bb153_13;
  TNode<IntPtrT> phi_bb153_14;
  TNode<FixedArray> phi_bb153_18;
  TNode<IntPtrT> phi_bb153_19;
  TNode<IntPtrT> phi_bb153_20;
  TNode<FixedArray> phi_bb153_23;
  TNode<IntPtrT> phi_bb153_24;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_9, &phi_bb153_11, &phi_bb153_12, &phi_bb153_13, &phi_bb153_14, &phi_bb153_18, &phi_bb153_19, &phi_bb153_20, &phi_bb153_23, &phi_bb153_24);
    ca_.Goto(&block151, phi_bb153_9, phi_bb153_11, phi_bb153_12, phi_bb153_13, phi_bb153_14, phi_bb153_18, phi_bb153_19, phi_bb153_20);
  }

  TNode<Uint32T> phi_bb151_9;
  TNode<JSAny> phi_bb151_11;
  TNode<FixedArray> phi_bb151_12;
  TNode<IntPtrT> phi_bb151_13;
  TNode<IntPtrT> phi_bb151_14;
  TNode<FixedArray> phi_bb151_18;
  TNode<IntPtrT> phi_bb151_19;
  TNode<IntPtrT> phi_bb151_20;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_9, &phi_bb151_11, &phi_bb151_12, &phi_bb151_13, &phi_bb151_14, &phi_bb151_18, &phi_bb151_19, &phi_bb151_20);
    ca_.Goto(&block149, phi_bb151_9, phi_bb151_11, phi_bb151_12, phi_bb151_13, phi_bb151_14, tmp224, phi_bb151_18, phi_bb151_19, phi_bb151_20);
  }

  TNode<Uint32T> phi_bb149_9;
  TNode<JSAny> phi_bb149_11;
  TNode<FixedArray> phi_bb149_12;
  TNode<IntPtrT> phi_bb149_13;
  TNode<IntPtrT> phi_bb149_14;
  TNode<FixedArray> phi_bb149_15;
  TNode<FixedArray> phi_bb149_18;
  TNode<IntPtrT> phi_bb149_19;
  TNode<IntPtrT> phi_bb149_20;
  TNode<IntPtrT> tmp269;
  TNode<BoolT> tmp270;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_9, &phi_bb149_11, &phi_bb149_12, &phi_bb149_13, &phi_bb149_14, &phi_bb149_15, &phi_bb149_18, &phi_bb149_19, &phi_bb149_20);
    tmp269 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp270 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb149_14}, TNode<IntPtrT>{tmp269});
    ca_.Branch(tmp270, &block188, std::vector<compiler::Node*>{phi_bb149_9, phi_bb149_11, phi_bb149_12, phi_bb149_13, phi_bb149_14, phi_bb149_15, phi_bb149_18, phi_bb149_19, phi_bb149_20, phi_bb149_14, phi_bb149_14}, &block189, std::vector<compiler::Node*>{phi_bb149_9, phi_bb149_11, phi_bb149_12, phi_bb149_13, phi_bb149_14, phi_bb149_15, phi_bb149_18, phi_bb149_19, phi_bb149_20, phi_bb149_14, phi_bb149_14});
  }

  TNode<Uint32T> phi_bb189_9;
  TNode<JSAny> phi_bb189_11;
  TNode<FixedArray> phi_bb189_12;
  TNode<IntPtrT> phi_bb189_13;
  TNode<IntPtrT> phi_bb189_14;
  TNode<FixedArray> phi_bb189_15;
  TNode<FixedArray> phi_bb189_18;
  TNode<IntPtrT> phi_bb189_19;
  TNode<IntPtrT> phi_bb189_20;
  TNode<IntPtrT> phi_bb189_23;
  TNode<IntPtrT> phi_bb189_24;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_9, &phi_bb189_11, &phi_bb189_12, &phi_bb189_13, &phi_bb189_14, &phi_bb189_15, &phi_bb189_18, &phi_bb189_19, &phi_bb189_20, &phi_bb189_23, &phi_bb189_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb188_9;
  TNode<JSAny> phi_bb188_11;
  TNode<FixedArray> phi_bb188_12;
  TNode<IntPtrT> phi_bb188_13;
  TNode<IntPtrT> phi_bb188_14;
  TNode<FixedArray> phi_bb188_15;
  TNode<FixedArray> phi_bb188_18;
  TNode<IntPtrT> phi_bb188_19;
  TNode<IntPtrT> phi_bb188_20;
  TNode<IntPtrT> phi_bb188_23;
  TNode<IntPtrT> phi_bb188_24;
  TNode<IntPtrT> tmp271;
  TNode<BoolT> tmp272;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_9, &phi_bb188_11, &phi_bb188_12, &phi_bb188_13, &phi_bb188_14, &phi_bb188_15, &phi_bb188_18, &phi_bb188_19, &phi_bb188_20, &phi_bb188_23, &phi_bb188_24);
    tmp271 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp272 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb188_24}, TNode<IntPtrT>{tmp271});
    ca_.Branch(tmp272, &block190, std::vector<compiler::Node*>{phi_bb188_9, phi_bb188_11, phi_bb188_12, phi_bb188_13, phi_bb188_14, phi_bb188_15, phi_bb188_18, phi_bb188_19, phi_bb188_20, phi_bb188_23, phi_bb188_24}, &block191, std::vector<compiler::Node*>{phi_bb188_9, phi_bb188_11, phi_bb188_12, phi_bb188_13, phi_bb188_14, phi_bb188_15, phi_bb188_18, phi_bb188_19, phi_bb188_20, phi_bb188_23, phi_bb188_24});
  }

  TNode<Uint32T> phi_bb191_9;
  TNode<JSAny> phi_bb191_11;
  TNode<FixedArray> phi_bb191_12;
  TNode<IntPtrT> phi_bb191_13;
  TNode<IntPtrT> phi_bb191_14;
  TNode<FixedArray> phi_bb191_15;
  TNode<FixedArray> phi_bb191_18;
  TNode<IntPtrT> phi_bb191_19;
  TNode<IntPtrT> phi_bb191_20;
  TNode<IntPtrT> phi_bb191_23;
  TNode<IntPtrT> phi_bb191_24;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_9, &phi_bb191_11, &phi_bb191_12, &phi_bb191_13, &phi_bb191_14, &phi_bb191_15, &phi_bb191_18, &phi_bb191_19, &phi_bb191_20, &phi_bb191_23, &phi_bb191_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb190_9;
  TNode<JSAny> phi_bb190_11;
  TNode<FixedArray> phi_bb190_12;
  TNode<IntPtrT> phi_bb190_13;
  TNode<IntPtrT> phi_bb190_14;
  TNode<FixedArray> phi_bb190_15;
  TNode<FixedArray> phi_bb190_18;
  TNode<IntPtrT> phi_bb190_19;
  TNode<IntPtrT> phi_bb190_20;
  TNode<IntPtrT> phi_bb190_23;
  TNode<IntPtrT> phi_bb190_24;
  TNode<BoolT> tmp273;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_9, &phi_bb190_11, &phi_bb190_12, &phi_bb190_13, &phi_bb190_14, &phi_bb190_15, &phi_bb190_18, &phi_bb190_19, &phi_bb190_20, &phi_bb190_23, &phi_bb190_24);
    tmp273 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb190_24}, TNode<IntPtrT>{phi_bb190_14});
    ca_.Branch(tmp273, &block192, std::vector<compiler::Node*>{phi_bb190_9, phi_bb190_11, phi_bb190_12, phi_bb190_13, phi_bb190_14, phi_bb190_15, phi_bb190_18, phi_bb190_19, phi_bb190_20, phi_bb190_23, phi_bb190_24}, &block193, std::vector<compiler::Node*>{phi_bb190_9, phi_bb190_11, phi_bb190_12, phi_bb190_13, phi_bb190_14, phi_bb190_15, phi_bb190_18, phi_bb190_19, phi_bb190_20, phi_bb190_23, phi_bb190_24});
  }

  TNode<Uint32T> phi_bb193_9;
  TNode<JSAny> phi_bb193_11;
  TNode<FixedArray> phi_bb193_12;
  TNode<IntPtrT> phi_bb193_13;
  TNode<IntPtrT> phi_bb193_14;
  TNode<FixedArray> phi_bb193_15;
  TNode<FixedArray> phi_bb193_18;
  TNode<IntPtrT> phi_bb193_19;
  TNode<IntPtrT> phi_bb193_20;
  TNode<IntPtrT> phi_bb193_23;
  TNode<IntPtrT> phi_bb193_24;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_9, &phi_bb193_11, &phi_bb193_12, &phi_bb193_13, &phi_bb193_14, &phi_bb193_15, &phi_bb193_18, &phi_bb193_19, &phi_bb193_20, &phi_bb193_23, &phi_bb193_24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb192_9;
  TNode<JSAny> phi_bb192_11;
  TNode<FixedArray> phi_bb192_12;
  TNode<IntPtrT> phi_bb192_13;
  TNode<IntPtrT> phi_bb192_14;
  TNode<FixedArray> phi_bb192_15;
  TNode<FixedArray> phi_bb192_18;
  TNode<IntPtrT> phi_bb192_19;
  TNode<IntPtrT> phi_bb192_20;
  TNode<IntPtrT> phi_bb192_23;
  TNode<IntPtrT> phi_bb192_24;
  TNode<IntPtrT> tmp274;
  TNode<TheHole> tmp275;
  TNode<FixedArray> tmp276;
  TNode<IntPtrT> tmp277;
  TNode<BoolT> tmp278;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_9, &phi_bb192_11, &phi_bb192_12, &phi_bb192_13, &phi_bb192_14, &phi_bb192_15, &phi_bb192_18, &phi_bb192_19, &phi_bb192_20, &phi_bb192_23, &phi_bb192_24);
    tmp274 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp275 = TheHole_0(state_);
    tmp276 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb192_12}, TNode<IntPtrT>{tmp274}, TNode<IntPtrT>{phi_bb192_14}, TNode<IntPtrT>{phi_bb192_24}, TNode<Hole>{tmp275});
    tmp277 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp278 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb192_20}, TNode<IntPtrT>{tmp277});
    ca_.Branch(tmp278, &block195, std::vector<compiler::Node*>{phi_bb192_9, phi_bb192_11, phi_bb192_12, phi_bb192_13, phi_bb192_14, phi_bb192_15, phi_bb192_18, phi_bb192_19, phi_bb192_20, phi_bb192_20, phi_bb192_20}, &block196, std::vector<compiler::Node*>{phi_bb192_9, phi_bb192_11, phi_bb192_12, phi_bb192_13, phi_bb192_14, phi_bb192_15, phi_bb192_18, phi_bb192_19, phi_bb192_20, phi_bb192_20, phi_bb192_20});
  }

  TNode<Uint32T> phi_bb196_9;
  TNode<JSAny> phi_bb196_11;
  TNode<FixedArray> phi_bb196_12;
  TNode<IntPtrT> phi_bb196_13;
  TNode<IntPtrT> phi_bb196_14;
  TNode<FixedArray> phi_bb196_15;
  TNode<FixedArray> phi_bb196_18;
  TNode<IntPtrT> phi_bb196_19;
  TNode<IntPtrT> phi_bb196_20;
  TNode<IntPtrT> phi_bb196_24;
  TNode<IntPtrT> phi_bb196_25;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_9, &phi_bb196_11, &phi_bb196_12, &phi_bb196_13, &phi_bb196_14, &phi_bb196_15, &phi_bb196_18, &phi_bb196_19, &phi_bb196_20, &phi_bb196_24, &phi_bb196_25);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb195_9;
  TNode<JSAny> phi_bb195_11;
  TNode<FixedArray> phi_bb195_12;
  TNode<IntPtrT> phi_bb195_13;
  TNode<IntPtrT> phi_bb195_14;
  TNode<FixedArray> phi_bb195_15;
  TNode<FixedArray> phi_bb195_18;
  TNode<IntPtrT> phi_bb195_19;
  TNode<IntPtrT> phi_bb195_20;
  TNode<IntPtrT> phi_bb195_24;
  TNode<IntPtrT> phi_bb195_25;
  TNode<IntPtrT> tmp279;
  TNode<BoolT> tmp280;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_9, &phi_bb195_11, &phi_bb195_12, &phi_bb195_13, &phi_bb195_14, &phi_bb195_15, &phi_bb195_18, &phi_bb195_19, &phi_bb195_20, &phi_bb195_24, &phi_bb195_25);
    tmp279 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp280 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb195_25}, TNode<IntPtrT>{tmp279});
    ca_.Branch(tmp280, &block197, std::vector<compiler::Node*>{phi_bb195_9, phi_bb195_11, phi_bb195_12, phi_bb195_13, phi_bb195_14, phi_bb195_15, phi_bb195_18, phi_bb195_19, phi_bb195_20, phi_bb195_24, phi_bb195_25}, &block198, std::vector<compiler::Node*>{phi_bb195_9, phi_bb195_11, phi_bb195_12, phi_bb195_13, phi_bb195_14, phi_bb195_15, phi_bb195_18, phi_bb195_19, phi_bb195_20, phi_bb195_24, phi_bb195_25});
  }

  TNode<Uint32T> phi_bb198_9;
  TNode<JSAny> phi_bb198_11;
  TNode<FixedArray> phi_bb198_12;
  TNode<IntPtrT> phi_bb198_13;
  TNode<IntPtrT> phi_bb198_14;
  TNode<FixedArray> phi_bb198_15;
  TNode<FixedArray> phi_bb198_18;
  TNode<IntPtrT> phi_bb198_19;
  TNode<IntPtrT> phi_bb198_20;
  TNode<IntPtrT> phi_bb198_24;
  TNode<IntPtrT> phi_bb198_25;
  if (block198.is_used()) {
    ca_.Bind(&block198, &phi_bb198_9, &phi_bb198_11, &phi_bb198_12, &phi_bb198_13, &phi_bb198_14, &phi_bb198_15, &phi_bb198_18, &phi_bb198_19, &phi_bb198_20, &phi_bb198_24, &phi_bb198_25);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb197_9;
  TNode<JSAny> phi_bb197_11;
  TNode<FixedArray> phi_bb197_12;
  TNode<IntPtrT> phi_bb197_13;
  TNode<IntPtrT> phi_bb197_14;
  TNode<FixedArray> phi_bb197_15;
  TNode<FixedArray> phi_bb197_18;
  TNode<IntPtrT> phi_bb197_19;
  TNode<IntPtrT> phi_bb197_20;
  TNode<IntPtrT> phi_bb197_24;
  TNode<IntPtrT> phi_bb197_25;
  TNode<BoolT> tmp281;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_9, &phi_bb197_11, &phi_bb197_12, &phi_bb197_13, &phi_bb197_14, &phi_bb197_15, &phi_bb197_18, &phi_bb197_19, &phi_bb197_20, &phi_bb197_24, &phi_bb197_25);
    tmp281 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb197_25}, TNode<IntPtrT>{phi_bb197_20});
    ca_.Branch(tmp281, &block199, std::vector<compiler::Node*>{phi_bb197_9, phi_bb197_11, phi_bb197_12, phi_bb197_13, phi_bb197_14, phi_bb197_15, phi_bb197_18, phi_bb197_19, phi_bb197_20, phi_bb197_24, phi_bb197_25}, &block200, std::vector<compiler::Node*>{phi_bb197_9, phi_bb197_11, phi_bb197_12, phi_bb197_13, phi_bb197_14, phi_bb197_15, phi_bb197_18, phi_bb197_19, phi_bb197_20, phi_bb197_24, phi_bb197_25});
  }

  TNode<Uint32T> phi_bb200_9;
  TNode<JSAny> phi_bb200_11;
  TNode<FixedArray> phi_bb200_12;
  TNode<IntPtrT> phi_bb200_13;
  TNode<IntPtrT> phi_bb200_14;
  TNode<FixedArray> phi_bb200_15;
  TNode<FixedArray> phi_bb200_18;
  TNode<IntPtrT> phi_bb200_19;
  TNode<IntPtrT> phi_bb200_20;
  TNode<IntPtrT> phi_bb200_24;
  TNode<IntPtrT> phi_bb200_25;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_9, &phi_bb200_11, &phi_bb200_12, &phi_bb200_13, &phi_bb200_14, &phi_bb200_15, &phi_bb200_18, &phi_bb200_19, &phi_bb200_20, &phi_bb200_24, &phi_bb200_25);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<Uint32T> phi_bb199_9;
  TNode<JSAny> phi_bb199_11;
  TNode<FixedArray> phi_bb199_12;
  TNode<IntPtrT> phi_bb199_13;
  TNode<IntPtrT> phi_bb199_14;
  TNode<FixedArray> phi_bb199_15;
  TNode<FixedArray> phi_bb199_18;
  TNode<IntPtrT> phi_bb199_19;
  TNode<IntPtrT> phi_bb199_20;
  TNode<IntPtrT> phi_bb199_24;
  TNode<IntPtrT> phi_bb199_25;
  TNode<IntPtrT> tmp282;
  TNode<TheHole> tmp283;
  TNode<FixedArray> tmp284;
  TNode<JSIteratorZipKeyedHelper> tmp285;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_9, &phi_bb199_11, &phi_bb199_12, &phi_bb199_13, &phi_bb199_14, &phi_bb199_15, &phi_bb199_18, &phi_bb199_19, &phi_bb199_20, &phi_bb199_24, &phi_bb199_25);
    tmp282 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp283 = TheHole_0(state_);
    tmp284 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb199_18}, TNode<IntPtrT>{tmp282}, TNode<IntPtrT>{phi_bb199_20}, TNode<IntPtrT>{phi_bb199_25}, TNode<Hole>{tmp283});
    tmp285 = NewJSIteratorZipKeyedHelper_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp276}, TNode<FixedArray>{phi_bb199_15}, TNode<Uint32T>{phi_bb199_9}, TNode<FixedArray>{tmp284});
    arguments.PopAndReturn(tmp285);
  }
}

TF_BUILTIN(IteratorZipKeyedHelperNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSIteratorZipKeyedHelper> parameter1 = UncheckedParameter<JSIteratorZipKeyedHelper>(Descriptor::kHelper);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp3(&ca_);
    compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>> tmp4(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp0 = IteratorZipHelperNextCommon_0(state_, TNode<Context>{parameter0}, TNode<JSIteratorZipHelper>{parameter1}, "Iterator.zipKeyed", &label1, &label2, &tmp3, &tmp4);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  TNode<Undefined> tmp5;
  TNode<True> tmp6;
  TNode<JSObject> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp5 = Undefined_0(state_);
    tmp6 = True_0(state_);
    tmp7 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp5}, TNode<Boolean>{tmp6});
    CodeStubAssembler(state_).Return(tmp7);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp3.value(), tmp4.value());
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<NativeContext> tmp8;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_NativeContext_0(state_, TNode<HeapObject>{parameter0}, &label9);
    ca_.Goto(&block10);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block11);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:2039:66");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Map> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<FixedArray> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<NameDictionary> tmp14;
  TNode<JSObject> tmp15;
  TNode<IntPtrT> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp10 = CodeStubAssembler(state_).LoadSlowObjectWithNullPrototypeMap(TNode<NativeContext>{tmp8});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp12 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp11});
    tmp13 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp12});
    tmp14 = CodeStubAssembler(state_).AllocateNameDictionary(TNode<IntPtrT>{tmp13});
    tmp15 = CodeStubAssembler(state_).AllocateJSObjectFromMap(TNode<Map>{tmp10}, TNode<Union<FixedArray, NameDictionary, PropertyArray, SwissNameDictionary>>{tmp14});
    tmp16 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block14, tmp16);
  }

  TNode<IntPtrT> phi_bb14_9;
  TNode<BoolT> tmp17;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_9);
    tmp17 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb14_9}, TNode<IntPtrT>{tmp13});
    ca_.Branch(tmp17, &block12, std::vector<compiler::Node*>{phi_bb14_9}, &block13, std::vector<compiler::Node*>{phi_bb14_9});
  }

  TNode<IntPtrT> phi_bb12_9;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<UintPtrT> tmp21;
  TNode<UintPtrT> tmp22;
  TNode<BoolT> tmp23;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_9);
    std::tie(tmp18, tmp19, tmp20) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp12}).Flatten();
    tmp21 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb12_9});
    tmp22 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp20});
    tmp23 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp21}, TNode<UintPtrT>{tmp22});
    ca_.Branch(tmp23, &block22, std::vector<compiler::Node*>{phi_bb12_9, phi_bb12_9, phi_bb12_9, phi_bb12_9, phi_bb12_9}, &block23, std::vector<compiler::Node*>{phi_bb12_9, phi_bb12_9, phi_bb12_9, phi_bb12_9, phi_bb12_9});
  }

  TNode<IntPtrT> phi_bb22_9;
  TNode<IntPtrT> phi_bb22_14;
  TNode<IntPtrT> phi_bb22_15;
  TNode<IntPtrT> phi_bb22_19;
  TNode<IntPtrT> phi_bb22_20;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Union<HeapObject, TaggedIndex>> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<Object> tmp28;
  TNode<JSAny> tmp29;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_9, &phi_bb22_14, &phi_bb22_15, &phi_bb22_19, &phi_bb22_20);
    tmp24 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb22_20});
    tmp25 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp19}, TNode<IntPtrT>{tmp24});
    std::tie(tmp26, tmp27) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp18}, TNode<IntPtrT>{tmp25}).Flatten();
    tmp28 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp26, tmp27});
    compiler::CodeAssemblerLabel label30(&ca_);
    tmp29 = Cast_JSAny_0(state_, TNode<Object>{tmp28}, &label30);
    ca_.Goto(&block26, phi_bb22_9);
    if (label30.is_used()) {
      ca_.Bind(&label30);
      ca_.Goto(&block27, phi_bb22_9);
    }
  }

  TNode<IntPtrT> phi_bb23_9;
  TNode<IntPtrT> phi_bb23_14;
  TNode<IntPtrT> phi_bb23_15;
  TNode<IntPtrT> phi_bb23_19;
  TNode<IntPtrT> phi_bb23_20;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_9, &phi_bb23_14, &phi_bb23_15, &phi_bb23_19, &phi_bb23_20);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb27_9;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_9);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:2053:58");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb26_9;
  TNode<Union<HeapObject, TaggedIndex>> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<UintPtrT> tmp35;
  TNode<BoolT> tmp36;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_9);
    std::tie(tmp31, tmp32, tmp33) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp0}).Flatten();
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb26_9});
    tmp35 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp33});
    tmp36 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp34}, TNode<UintPtrT>{tmp35});
    ca_.Branch(tmp36, &block34, std::vector<compiler::Node*>{phi_bb26_9, phi_bb26_9, phi_bb26_9, phi_bb26_9, phi_bb26_9}, &block35, std::vector<compiler::Node*>{phi_bb26_9, phi_bb26_9, phi_bb26_9, phi_bb26_9, phi_bb26_9});
  }

  TNode<IntPtrT> phi_bb34_9;
  TNode<IntPtrT> phi_bb34_15;
  TNode<IntPtrT> phi_bb34_16;
  TNode<IntPtrT> phi_bb34_20;
  TNode<IntPtrT> phi_bb34_21;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<Union<HeapObject, TaggedIndex>> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Object> tmp41;
  TNode<JSAny> tmp42;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_9, &phi_bb34_15, &phi_bb34_16, &phi_bb34_20, &phi_bb34_21);
    tmp37 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb34_21});
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp32}, TNode<IntPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp31}, TNode<IntPtrT>{tmp38}).Flatten();
    tmp41 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp39, tmp40});
    compiler::CodeAssemblerLabel label43(&ca_);
    tmp42 = Cast_JSAny_0(state_, TNode<Object>{tmp41}, &label43);
    ca_.Goto(&block38, phi_bb34_9);
    if (label43.is_used()) {
      ca_.Bind(&label43);
      ca_.Goto(&block39, phi_bb34_9);
    }
  }

  TNode<IntPtrT> phi_bb35_9;
  TNode<IntPtrT> phi_bb35_15;
  TNode<IntPtrT> phi_bb35_16;
  TNode<IntPtrT> phi_bb35_20;
  TNode<IntPtrT> phi_bb35_21;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_9, &phi_bb35_15, &phi_bb35_16, &phi_bb35_20, &phi_bb35_21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb39_9;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_9);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/iterator-helpers.tq:2054:64");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb38_9;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_9);
    CodeStubAssembler(state_).CallRuntime(Runtime::kCreateDataProperty, parameter0, tmp15, tmp29, tmp42);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp45 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb38_9}, TNode<IntPtrT>{tmp44});
    ca_.Goto(&block14, tmp45);
  }

  TNode<IntPtrT> phi_bb13_9;
  TNode<False> tmp46;
  TNode<JSObject> tmp47;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_9);
    MarkIteratorHelperAsFinishedExecuting_0(state_, TNode<JSIteratorHelper>{parameter1});
    tmp46 = False_0(state_);
    tmp47 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp15}, TNode<Boolean>{tmp46});
    CodeStubAssembler(state_).Return(tmp47);
  }
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=11&c=7
TNode<Smi> SmiTag_JSIteratorHelperState_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiFromUint32(TNode<Uint32T>{p_value});
    tmp1 = (TNode<Smi>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=72&c=18
TNode<JSIteratorHelper> Cast_JSIteratorHelper_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{p_o}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<JSIteratorHelper> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSIteratorHelper_0(state_, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block5);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block7);
  return TNode<JSIteratorHelper>{tmp2};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1272&c=10
TNode<BoolT> Is_JSReceiver_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{p_context}, TNode<Object>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1505&c=11
TNode<Smi> SmiTag_JSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiFromUint32(TNode<Uint32T>{p_value});
    tmp1 = (TNode<Smi>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1615&c=40
TorqueStructConstantIterator_Undefined_0 ConstantIterator_Undefined_0(compiler::CodeAssemblerState* state_, TNode<Undefined> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructConstantIterator_Undefined_0{TNode<Undefined>{p_value}};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1615&c=15
TNode<FixedArray> NewFixedArray_ConstantIterator_Undefined_0(compiler::CodeAssemblerState* state_, TNode<IntPtrT> p_length, TorqueStructConstantIterator_Undefined_0 p_it) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{p_length});
    tmp1 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp0});
    tmp2 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<FixedArray> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = kEmptyFixedArray_0(state_);
    ca_.Goto(&block1, tmp4);
  }

  TNode<Uint32T> tmp5;
  TNode<BoolT> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_uint32_constexpr_int31_0(state_, FixedArray::kMaxLength);
    tmp6 = CodeStubAssembler(state_).Uint32GreaterThan(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp5});
    ca_.Branch(tmp6, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp7 = kNoContext_0(state_);
    CodeStubAssembler(state_).CallRuntime(Runtime::kFatalProcessOutOfMemoryInvalidArrayLength, tmp7);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Map> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<BoolT> tmp12;
  TNode<BoolT> tmp13;
  TNode<HeapObject> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<FixedArray> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp8 = kFixedArrayMap_0(state_);
    tmp9 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp1});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp11 = AddIndexedFieldSizeToObjectSize_0(state_, TNode<IntPtrT>{tmp10}, TNode<IntPtrT>{tmp9}, CastIfEnumClass<int32_t>(kTaggedSize));
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp13 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp14 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp11}, TNode<Map>{tmp8}, TNode<BoolT>{tmp12}, TNode<BoolT>{tmp13});
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp14, tmp15}, tmp8);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Uint32T>(CodeStubAssembler::Reference{tmp14, tmp16}, tmp1);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    InitializeFieldsFromIterator_Object_ConstantIterator_Undefined_0(state_, TorqueStructSlice_Object_MutableReference_Object_0{TNode<Union<HeapObject, TaggedIndex>>{tmp14}, TNode<IntPtrT>{tmp17}, TNode<IntPtrT>{tmp9}, TorqueStructUnsafe_0{}}, TorqueStructConstantIterator_Undefined_0{TNode<Undefined>{p_it.value}});
    tmp18 = TORQUE_CAST(TNode<HeapObject>{tmp14});
    ca_.Goto(&block1, tmp18);
  }

  TNode<FixedArray> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6, phi_bb1_2);
  }

  TNode<FixedArray> phi_bb6_2;
    ca_.Bind(&block6, &phi_bb6_2);
  return TNode<FixedArray>{phi_bb6_2};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1698&c=16
TNode<Uint32T> SmiUntag_JSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Int32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<Uint32T> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_Smi_SmiTagged_JSIteratorZipHelperMode_0(state_, TNode<Smi>{p_value});
    tmp1 = CodeStubAssembler(state_).SmiToInt32(TNode<Smi>{tmp0});
    tmp2 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp1});
    tmp3 = (TNode<Uint32T>{tmp2});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp3};
}

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1963&c=13
TNode<PropertyDescriptorObject> Cast_PropertyDescriptorObject_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{p_o}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<PropertyDescriptorObject> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_PropertyDescriptorObject_0(state_, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block5);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block7);
  return TNode<PropertyDescriptorObject>{tmp2};
}

} // namespace internal
} // namespace v8
