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
#include "torque-generated/src/builtins/object-fromentries-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/collections-tq-csa.h"
#include "torque-generated/src/builtins/conversion-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/iterator-tq-csa.h"
#include "torque-generated/src/builtins/object-fromentries-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/oddball-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/object-fromentries.tq?l=7&c=1
TNode<JSObject> ObjectFromEntriesFastCase_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_iterable, compiler::CodeAssemblerLabel* label_IfSlow) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArrayWithNoCustomIteration_1(state_, TNode<Context>{p_context}, TNode<Object>{p_iterable}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp2;
  TNode<FixedArrayBase> tmp3;
  TNode<FixedArray> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp3 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp2});
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp3}, &label5);
    ca_.Goto(&block7);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1);
  }

  TNode<Smi> tmp6;
  TNode<JSObject> tmp7;
  TNode<Smi> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp6 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    tmp7 = NewJSObject_0(state_, TNode<Context>{p_context});
    tmp8 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block11, tmp8);
  }

  TNode<Smi> phi_bb11_7;
  TNode<BoolT> tmp9;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    tmp9 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb11_7}, TNode<Smi>{tmp6});
    ca_.Branch(tmp9, &block9, std::vector<compiler::Node*>{phi_bb11_7}, &block10, std::vector<compiler::Node*>{phi_bb11_7});
  }

  TNode<Smi> phi_bb9_7;
  TNode<JSAny> tmp10;
  TNode<JSAny> tmp11;
  TNode<JSAny> tmp12;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_7);
    tmp10 = LoadElementOrUndefined_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp4}, TNode<Smi>{phi_bb9_7});
    compiler::CodeAssemblerLabel label13(&ca_);
    std::tie(tmp11, tmp12) = LoadKeyValuePairNoSideEffects_0(state_, TNode<Context>{p_context}, TNode<JSAny>{tmp10}, &label13).Flatten();
    ca_.Goto(&block13, phi_bb9_7);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block14, phi_bb9_7);
    }
  }

  TNode<Smi> phi_bb14_7;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_7);
    ca_.Goto(&block1);
  }

  TNode<Smi> phi_bb13_7;
  TNode<Name> tmp14;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_7);
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = Cast_Name_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp11}, &label15);
    ca_.Goto(&block17, phi_bb13_7);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block18, phi_bb13_7);
    }
  }

  TNode<Smi> phi_bb18_7;
  TNode<Number> tmp16;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_7);
    compiler::CodeAssemblerLabel label17(&ca_);
    tmp16 = Cast_Number_0(state_, TNode<Object>{ca_.UncheckedCast<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, Undefined>>(tmp11)}, &label17);
    ca_.Goto(&block21, phi_bb18_7);
    if (label17.is_used()) {
      ca_.Bind(&label17);
      ca_.Goto(&block22, phi_bb18_7);
    }
  }

  TNode<Smi> phi_bb17_7;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    CodeStubAssembler(state_).CallRuntime(Runtime::kCreateDataProperty, p_context, tmp7, tmp11, tmp12);
    ca_.Goto(&block15, phi_bb17_7);
  }

  TNode<Smi> phi_bb22_7;
  TNode<Oddball> tmp18;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7);
    compiler::CodeAssemblerLabel label19(&ca_);
    tmp18 = Cast_Oddball_0(state_, TNode<HeapObject>{ca_.UncheckedCast<Union<BigInt, Boolean, JSReceiver, Null, Undefined>>(tmp11)}, &label19);
    ca_.Goto(&block25, phi_bb22_7);
    if (label19.is_used()) {
      ca_.Bind(&label19);
      ca_.Goto(&block26, phi_bb22_7);
    }
  }

  TNode<Smi> phi_bb21_7;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7);
    CodeStubAssembler(state_).CallRuntime(Runtime::kCreateDataProperty, p_context, tmp7, tmp11, tmp12);
    ca_.Goto(&block19, phi_bb21_7);
  }

  TNode<Smi> phi_bb26_7;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_7);
    ca_.Goto(&block1);
  }

  TNode<Smi> phi_bb25_7;
  TNode<IntPtrT> tmp20;
  TNode<String> tmp21;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_7);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp21 = CodeStubAssembler(state_).LoadReference<String>(CodeStubAssembler::Reference{tmp18, tmp20});
    CodeStubAssembler(state_).CallRuntime(Runtime::kCreateDataProperty, p_context, tmp7, tmp21, tmp12);
    ca_.Goto(&block19, phi_bb25_7);
  }

  TNode<Smi> phi_bb19_7;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_7);
    ca_.Goto(&block15, phi_bb19_7);
  }

  TNode<Smi> phi_bb15_7;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_7);
    tmp22 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp23 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb15_7}, TNode<Smi>{tmp22});
    ca_.Goto(&block11, tmp23);
  }

  TNode<Smi> phi_bb10_7;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_7);
    ca_.Goto(&block27);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_IfSlow);
  }

    ca_.Bind(&block27);
  return TNode<JSObject>{tmp7};
}

TF_BUILTIN(ObjectFromEntries, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    tmp2 = CodeStubAssembler(state_).IsNullOrUndefined(TNode<Object>{tmp1});
    ca_.Branch(tmp2, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kNotIterable));
  }

  TNode<JSObject> tmp3;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = ObjectFromEntriesFastCase_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp1}, &label4);
    ca_.Goto(&block7);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block8);
    }
  }

  TNode<JSObject> tmp5;
  TNode<Map> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<JSAny> tmp8;
  TNode<BoolT> tmp9;
      TNode<JSAny> tmp11;
  TNode<BoolT> tmp12;
      TNode<JSAny> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp5 = NewJSObject_0(state_, TNode<Context>{parameter0});
    tmp6 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    std::tie(tmp7, tmp8) = IteratorBuiltinsAssembler(state_).GetIterator(TNode<Context>{parameter0}, TNode<JSAny>{tmp1}).Flatten();
    compiler::CodeAssemblerExceptionHandlerLabel catch10__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch10__label);
    tmp9 = CodeStubAssembler(state_).IsNullOrUndefined(TNode<Object>{tmp7});
    }
    if (catch10__label.is_used()) {
      compiler::CodeAssemblerLabel catch10_skip(&ca_);
      ca_.Goto(&catch10_skip);
      ca_.Bind(&catch10__label, &tmp11);
      ca_.Goto(&block13);
      ca_.Bind(&catch10_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch13__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch13__label);
    tmp12 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp9});
    }
    if (catch13__label.is_used()) {
      compiler::CodeAssemblerLabel catch13_skip(&ca_);
      ca_.Goto(&catch13_skip);
      ca_.Bind(&catch13__label, &tmp14);
      ca_.Goto(&block14);
      ca_.Bind(&catch13_skip);
    }
    ca_.Branch(tmp12, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    arguments.PopAndReturn(tmp3);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp15;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp15 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp11, tmp15);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp16;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp16 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp14, tmp16);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/object-fromentries.tq", 60});
      CodeStubAssembler(state_).FailAssert("Torque assert '!IsNullOrUndefined(i.object)' failed", pos_stack);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block17);
  }

  TNode<BoolT> tmp17;
      TNode<JSAny> tmp19;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    compiler::CodeAssemblerExceptionHandlerLabel catch18__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch18__label);
    tmp17 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    }
    if (catch18__label.is_used()) {
      compiler::CodeAssemblerLabel catch18_skip(&ca_);
      ca_.Goto(&catch18_skip);
      ca_.Bind(&catch18__label, &tmp19);
      ca_.Goto(&block18);
      ca_.Bind(&catch18_skip);
    }
    ca_.Branch(tmp17, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<Union<JSMessageObject, TheHole>> tmp20;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp20 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp19, tmp20);
  }

  TNode<JSReceiver> tmp21;
      TNode<JSAny> tmp24;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label22(&ca_);
    compiler::CodeAssemblerExceptionHandlerLabel catch23__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch23__label);
    tmp21 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp7}, TNode<JSAny>{tmp8}}, TNode<Map>{tmp6}, &label22);
    }
    if (catch23__label.is_used()) {
      compiler::CodeAssemblerLabel catch23_skip(&ca_);
      ca_.Goto(&catch23_skip);
      ca_.Bind(&catch23__label, &tmp24);
      ca_.Goto(&block23);
      ca_.Bind(&catch23_skip);
    }
    ca_.Goto(&block21);
    if (label22.is_used()) {
      ca_.Bind(&label22);
      ca_.Goto(&block22);
    }
  }

  TNode<Union<JSMessageObject, TheHole>> tmp25;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp25 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp24, tmp25);
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    arguments.PopAndReturn(tmp5);
  }

  TNode<JSAny> tmp26;
      TNode<JSAny> tmp28;
  TNode<JSAny> tmp29;
  TNode<JSAny> tmp30;
      TNode<JSAny> tmp32;
      TNode<JSAny> tmp34;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    compiler::CodeAssemblerExceptionHandlerLabel catch27__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch27__label);
    tmp26 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp21}, TNode<Map>{tmp6});
    }
    if (catch27__label.is_used()) {
      compiler::CodeAssemblerLabel catch27_skip(&ca_);
      ca_.Goto(&catch27_skip);
      ca_.Bind(&catch27__label, &tmp28);
      ca_.Goto(&block24);
      ca_.Bind(&catch27_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch31__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch31__label);
    std::tie(tmp29, tmp30) = LoadKeyValuePair_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp26}).Flatten();
    }
    if (catch31__label.is_used()) {
      compiler::CodeAssemblerLabel catch31_skip(&ca_);
      ca_.Goto(&catch31_skip);
      ca_.Bind(&catch31__label, &tmp32);
      ca_.Goto(&block25);
      ca_.Bind(&catch31_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch33__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch33__label);
    CodeStubAssembler(state_).CallRuntime(Runtime::kCreateDataProperty, parameter0, tmp5, tmp29, tmp30);
    }
    if (catch33__label.is_used()) {
      compiler::CodeAssemblerLabel catch33_skip(&ca_);
      ca_.Goto(&catch33_skip);
      ca_.Bind(&catch33__label, &tmp34);
      ca_.Goto(&block26);
      ca_.Bind(&catch33_skip);
    }
    ca_.Goto(&block17);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp35;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp35 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp28, tmp35);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp36;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp36 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp32, tmp36);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp37;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp37 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block10, tmp34, tmp37);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    arguments.PopAndReturn(tmp5);
  }

  TNode<JSAny> phi_bb10_11;
  TNode<Union<JSMessageObject, TheHole>> phi_bb10_12;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_11, &phi_bb10_12);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp7});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb10_11, phi_bb10_12);
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/object-fromentries.tq?l=10&c=5
TNode<JSArray> Cast_FastJSArrayWithNoCustomIteration_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSArray> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSArrayWithNoCustomIteration_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSArray>{tmp2};
}

} // namespace internal
} // namespace v8
