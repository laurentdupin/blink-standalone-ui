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
#include "torque-generated/src/builtins/promise-race-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/iterator-tq-csa.h"
#include "torque-generated/src/builtins/promise-abstract-operations-tq-csa.h"
#include "torque-generated/src/builtins/promise-any-tq-csa.h"
#include "torque-generated/src/builtins/promise-constructor-tq-csa.h"
#include "torque-generated/src/builtins/promise-race-tq-csa.h"
#include "torque-generated/src/builtins/promise-resolve-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/js-promise-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(PromiseRace, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kIterable);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, JSAny, Union<JSMessageObject, TheHole>> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
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
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kCalledOnNonObject), "Promise.race");
  }

  TNode<BoolT> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = Is_NativeContext_Context_0(state_, TNode<Context>{parameter0}, TNode<Context>{parameter0});
    ca_.Branch(tmp2, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-race.tq", 17});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<NativeContext>(context)' failed", pos_stack);
    }
  }

  TNode<NativeContext> tmp3;
  TNode<False> tmp4;
  TNode<PromiseCapability> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<JSAny> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<JSAny> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<JSReceiver, Undefined>> tmp11;
  TNode<BoolT> tmp12;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp3 = UnsafeCast_NativeContext_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter0});
    tmp4 = False_0(state_);
    tmp5 = ca_.CallBuiltin<PromiseCapability>(Builtin::kNewPromiseCapability, parameter0, tmp0, tmp4);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp5, tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp9 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp11 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Undefined>>(CodeStubAssembler::Reference{tmp5, tmp10});
    tmp12 = Is_Constructor_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0});
    ca_.Branch(tmp12, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-race.tq", 29});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<Constructor>(receiver)' failed", pos_stack);
    }
  }

  TNode<JSReceiver> tmp13;
  TNode<BoolT> tmp14;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp13 = UnsafeCast_Constructor_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp0});
    tmp14 = CodeStubAssembler(state_).IsDebugActive();
    ca_.Branch(tmp14, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Symbol> tmp15;
  TNode<True> tmp16;
  TNode<Object> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = kPromiseForwardingHandlerSymbol_0(state_);
    tmp16 = True_0(state_);
    tmp17 = CodeStubAssembler(state_).SetPropertyStrict(TNode<Context>{parameter0}, TNode<JSAny>{tmp9}, TNode<Object>{tmp15}, TNode<Object>{tmp16});
    ca_.Goto(&block10);
  }

  TNode<JSAny> tmp18;
      TNode<JSAny> tmp20;
  TNode<JSReceiver> tmp21;
  TNode<JSAny> tmp22;
      TNode<JSAny> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Union<HeapObject, TaggedIndex>> tmp26;
  TNode<IntPtrT> tmp27;
      TNode<JSAny> tmp29;
  TNode<Map> tmp30;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    compiler::CodeAssemblerExceptionHandlerLabel catch19__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch19__label);
    tmp18 = GetPromiseResolve_0(state_, TNode<Context>{parameter0}, TNode<NativeContext>{tmp3}, TNode<JSReceiver>{tmp13});
    }
    if (catch19__label.is_used()) {
      compiler::CodeAssemblerLabel catch19_skip(&ca_);
      ca_.Goto(&catch19_skip);
      ca_.Bind(&catch19__label, &tmp20);
      ca_.Goto(&block15);
      ca_.Bind(&catch19_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch23__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch23__label);
    std::tie(tmp21, tmp22) = IteratorBuiltinsAssembler(state_).GetIterator(TNode<Context>{parameter0}, TNode<JSAny>{parameter2}).Flatten();
    }
    if (catch23__label.is_used()) {
      compiler::CodeAssemblerLabel catch23_skip(&ca_);
      ca_.Goto(&catch23_skip);
      ca_.Bind(&catch23__label, &tmp24);
      ca_.Goto(&block16);
      ca_.Bind(&catch23_skip);
    }
    tmp25 = ITERATOR_RESULT_MAP_INDEX_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch28__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch28__label);
    std::tie(tmp26, tmp27) = NativeContextSlot_Map_1(state_, TNode<NativeContext>{tmp3}, TNode<IntPtrT>{tmp25}).Flatten();
    }
    if (catch28__label.is_used()) {
      compiler::CodeAssemblerLabel catch28_skip(&ca_);
      ca_.Goto(&catch28_skip);
      ca_.Bind(&catch28__label, &tmp29);
      ca_.Goto(&block19);
      ca_.Bind(&catch28_skip);
    }
    tmp30 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp26, tmp27});
    ca_.Goto(&block22);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp31;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp31 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block14, ca_.Uninitialized<JSAny>(), tmp20, tmp31);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp32;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp32 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block14, tmp18, tmp24, tmp32);
  }

  TNode<JSAny> phi_bb14_10;
  TNode<JSAny> phi_bb14_13;
  TNode<Union<JSMessageObject, TheHole>> phi_bb14_14;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_10, &phi_bb14_13, &phi_bb14_14);
    ca_.Goto(&block12, phi_bb14_13);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp33;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp33 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp29, tmp33);
  }

  TNode<BoolT> tmp34;
      TNode<JSAny> tmp36;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    compiler::CodeAssemblerExceptionHandlerLabel catch35__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch35__label);
    tmp34 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch35__label.is_used()) {
      compiler::CodeAssemblerLabel catch35_skip(&ca_);
      ca_.Goto(&catch35_skip);
      ca_.Bind(&catch35__label, &tmp36);
      ca_.Goto(&block23);
      ca_.Bind(&catch35_skip);
    }
    ca_.Branch(tmp34, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp37;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp37 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp36, tmp37);
  }

  TNode<JSReceiver> tmp38;
      TNode<JSAny> tmp41;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    compiler::CodeAssemblerLabel label39(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch40__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch40__label);
    tmp38 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp21}, TNode<JSAny>{tmp22}}, TNode<Map>{tmp30}, &label39);
    }
    if (catch40__label.is_used()) {
      compiler::CodeAssemblerLabel catch40_skip(&ca_);
      ca_.Goto(&catch40_skip);
      ca_.Bind(&catch40__label, &tmp41);
      ca_.Goto(&block30);
      ca_.Bind(&catch40_skip);
    }
    ca_.Goto(&block28);
    if (label39.is_used()) {
      ca_.Bind(&label39);
      ca_.Goto(&block29);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp42;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp42 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block25, tmp41, tmp42);
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<JSAny> tmp43;
      TNode<JSAny> tmp45;
  TNode<JSAny> tmp46;
      TNode<JSAny> tmp48;
  TNode<String> tmp49;
  TNode<JSAny> tmp50;
      TNode<JSAny> tmp52;
  TNode<JSAny> tmp53;
      TNode<JSAny> tmp55;
  TNode<JSAny> tmp56;
      TNode<JSAny> tmp58;
  TNode<JSAny> tmp59;
      TNode<JSAny> tmp61;
  TNode<BoolT> tmp62;
      TNode<JSAny> tmp64;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    compiler::CodeAssemblerExceptionHandlerLabel catch44__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch44__label);
    tmp43 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp38}, TNode<Map>{tmp30});
    }
    if (catch44__label.is_used()) {
      compiler::CodeAssemblerLabel catch44_skip(&ca_);
      ca_.Goto(&catch44_skip);
      ca_.Bind(&catch44__label, &tmp45);
      ca_.Goto(&block31);
      ca_.Bind(&catch44_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch47__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch47__label);
    tmp46 = CallResolve_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp13}, TNode<JSAny>{tmp18}, TNode<JSAny>{tmp43});
    }
    if (catch47__label.is_used()) {
      compiler::CodeAssemblerLabel catch47_skip(&ca_);
      ca_.Goto(&catch47_skip);
      ca_.Bind(&catch47__label, &tmp48);
      ca_.Goto(&block32);
      ca_.Bind(&catch47_skip);
    }
    tmp49 = kThenString_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch51__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch51__label);
    tmp50 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp46}, TNode<JSAny>{tmp49});
    }
    if (catch51__label.is_used()) {
      compiler::CodeAssemblerLabel catch51_skip(&ca_);
      ca_.Goto(&catch51_skip);
      ca_.Bind(&catch51__label, &tmp52);
      ca_.Goto(&block33);
      ca_.Bind(&catch51_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch54__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch54__label);
    tmp53 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    }
    if (catch54__label.is_used()) {
      compiler::CodeAssemblerLabel catch54_skip(&ca_);
      ca_.Goto(&catch54_skip);
      ca_.Bind(&catch54__label, &tmp55);
      ca_.Goto(&block34);
      ca_.Bind(&catch54_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch57__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch57__label);
    tmp56 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp9});
    }
    if (catch57__label.is_used()) {
      compiler::CodeAssemblerLabel catch57_skip(&ca_);
      ca_.Goto(&catch57_skip);
      ca_.Bind(&catch57__label, &tmp58);
      ca_.Goto(&block35);
      ca_.Bind(&catch57_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch60__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch60__label);
    tmp59 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp50}, TNode<JSAny>{tmp46}, TNode<JSAny>{tmp53}, TNode<JSAny>{tmp56});
    }
    if (catch60__label.is_used()) {
      compiler::CodeAssemblerLabel catch60_skip(&ca_);
      ca_.Goto(&catch60_skip);
      ca_.Bind(&catch60__label, &tmp61);
      ca_.Goto(&block36);
      ca_.Bind(&catch60_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch63__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch63__label);
    tmp62 = CodeStubAssembler(state_).IsDebugActive();
    }
    if (catch63__label.is_used()) {
      compiler::CodeAssemblerLabel catch63_skip(&ca_);
      ca_.Goto(&catch63_skip);
      ca_.Bind(&catch63__label, &tmp64);
      ca_.Goto(&block39);
      ca_.Bind(&catch63_skip);
    }
    ca_.Branch(tmp62, &block40, std::vector<compiler::Node*>{}, &block41, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp65;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp65 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block25, tmp45, tmp65);
  }

  TNode<JSAny> phi_bb25_15;
  TNode<Union<JSMessageObject, TheHole>> phi_bb25_16;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_15, &phi_bb25_16);
    ca_.Goto(&block12, phi_bb25_15);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp66;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp66 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp48, tmp66);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp67;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp67 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp52, tmp67);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp68;
  if (block34.is_used()) {
    ca_.Bind(&block34);
    tmp68 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp55, tmp68);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp69;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp69 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp58, tmp69);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp70;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp70 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp61, tmp70);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp71;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp71 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp64, tmp71);
  }

  TNode<BoolT> tmp72;
      TNode<JSAny> tmp74;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    compiler::CodeAssemblerExceptionHandlerLabel catch73__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch73__label);
    tmp72 = Is_JSPromise_JSReceiver_OR_Undefined_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Undefined>>{tmp11});
    }
    if (catch73__label.is_used()) {
      compiler::CodeAssemblerLabel catch73_skip(&ca_);
      ca_.Goto(&catch73_skip);
      ca_.Bind(&catch73__label, &tmp74);
      ca_.Goto(&block43);
      ca_.Bind(&catch73_skip);
    }
    ca_.Goto(&block42, tmp72);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp75;
  if (block43.is_used()) {
    ca_.Bind(&block43);
    tmp75 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp74, tmp75);
  }

  TNode<BoolT> tmp76;
      TNode<JSAny> tmp78;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    compiler::CodeAssemblerExceptionHandlerLabel catch77__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch77__label);
    tmp76 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    }
    if (catch77__label.is_used()) {
      compiler::CodeAssemblerLabel catch77_skip(&ca_);
      ca_.Goto(&catch77_skip);
      ca_.Bind(&catch77__label, &tmp78);
      ca_.Goto(&block44);
      ca_.Bind(&catch77_skip);
    }
    ca_.Goto(&block42, tmp76);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp79;
  if (block44.is_used()) {
    ca_.Bind(&block44);
    tmp79 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp78, tmp79);
  }

  TNode<BoolT> phi_bb42_19;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_19);
    ca_.Branch(phi_bb42_19, &block37, std::vector<compiler::Node*>{}, &block38, std::vector<compiler::Node*>{});
  }

  TNode<Symbol> tmp80;
  TNode<Object> tmp81;
      TNode<JSAny> tmp83;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp80 = kPromiseHandledBySymbol_0(state_);
    compiler::CodeAssemblerExceptionHandlerLabel catch82__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch82__label);
    tmp81 = CodeStubAssembler(state_).SetPropertyStrict(TNode<Context>{parameter0}, TNode<JSAny>{tmp59}, TNode<Object>{tmp80}, TNode<Object>{tmp11});
    }
    if (catch82__label.is_used()) {
      compiler::CodeAssemblerLabel catch82_skip(&ca_);
      ca_.Goto(&catch82_skip);
      ca_.Bind(&catch82__label, &tmp83);
      ca_.Goto(&block45);
      ca_.Bind(&catch82_skip);
    }
    ca_.Goto(&block38);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp84;
  if (block45.is_used()) {
    ca_.Bind(&block45);
    tmp84 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block18, tmp83, tmp84);
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    ca_.Goto(&block22);
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/promise-race.tq:101:3");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb18_13;
  TNode<Union<JSMessageObject, TheHole>> phi_bb18_14;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_13, &phi_bb18_14);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp21});
    ca_.Goto(&block12, phi_bb18_13);
  }

  TNode<JSAny> phi_bb12_10;
  TNode<JSAny> tmp85;
  TNode<Undefined> tmp86;
  TNode<JSAny> tmp87;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_10);
    tmp85 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp9});
    tmp86 = Undefined_0(state_);
    tmp87 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp85}, TNode<JSAny>{tmp86}, TNode<JSAny>{phi_bb12_10});
    CodeStubAssembler(state_).Return(tmp11);
  }
}

// https://crsrc.org/c/v8/src/builtins/promise-race.tq?l=88&c=32
TNode<BoolT> Is_JSPromise_JSReceiver_OR_Undefined_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Union<JSReceiver, Undefined>> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSPromise> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSPromise_0(state_, TNode<HeapObject>{p_o}, &label1);
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

} // namespace internal
} // namespace v8
