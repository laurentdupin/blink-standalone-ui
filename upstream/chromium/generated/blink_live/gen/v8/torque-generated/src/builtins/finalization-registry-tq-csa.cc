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
#include "torque-generated/src/builtins/finalization-registry-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/boolean-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/finalization-registry-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/js-weak-refs-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/finalization-registry.tq?l=18&c=1
void PushCell_0(compiler::CodeAssemblerState* state_, TNode<JSFinalizationRegistry> p_finalizationRegistry, TNode<WeakCell> p_cell) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSFinalizationRegistry> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSFinalizationRegistry>(CodeStubAssembler::Reference{p_cell, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{p_finalizationRegistry}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1});
    ca_.Branch(tmp2, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/finalization-registry.tq", 20});
      CodeStubAssembler(state_).FailAssert("Torque assert 'finalizationRegistry == cell.finalization_registry' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Union<Undefined, WeakCell>> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Union<Undefined, WeakCell>> tmp7;
  TNode<Undefined> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp5 = CodeStubAssembler(state_).LoadReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{p_finalizationRegistry, tmp4});
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{p_cell, tmp3}, tmp5);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp7 = CodeStubAssembler(state_).LoadReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{p_finalizationRegistry, tmp6});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Undefined_2(state_, TNode<HeapObject>{tmp7}, &label9);
    ca_.Goto(&block6);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block7);
    }
  }

  TNode<IntPtrT> tmp10;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{ca_.UncheckedCast<WeakCell>(tmp7), tmp10}, p_cell);
    ca_.Goto(&block4);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block4);
  }

  TNode<IntPtrT> tmp11;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{p_finalizationRegistry, tmp11}, p_cell);
    ca_.Goto(&block8);
  }

    ca_.Bind(&block8);
}

TF_BUILTIN(FinalizationRegistryConstructor, CodeStubAssembler) {
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
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kJSNewTarget);
  USE(parameter2);
  TNode<JSFunction> parameter3 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter3);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kWeakReferences));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Undefined> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Undefined_0(state_);
    tmp1 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{parameter2}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kConstructorNotFunction), "FinalizationRegistry");
  }

  TNode<IntPtrT> tmp2;
  TNode<BoolT> tmp3;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.actual_count}, TNode<IntPtrT>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kWeakRefsCleanupMustBeCallable));
  }

  TNode<IntPtrT> tmp4;
  TNode<JSAny> tmp5;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp4});
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp5}, &label7);
    ca_.Goto(&block7);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kWeakRefsCleanupMustBeCallable));
  }

  TNode<JSReceiver> tmp8;
  TNode<Map> tmp9;
  TNode<JSObject> tmp10;
  TNode<JSFinalizationRegistry> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Int32T> tmp15;
  TNode<Uint32T> tmp16;
  TNode<Uint32T> tmp17;
  TNode<BoolT> tmp18;
  TNode<Uint32T> tmp19;
  TNode<Smi> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Union<Undefined, WeakCell>> tmp22;
  TNode<Undefined> tmp23;
  TNode<BoolT> tmp24;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp9 = GetDerivedMap_0(state_, TNode<Context>{parameter0}, TNode<JSFunction>{parameter3}, TNode<JSReceiver>{tmp8});
    tmp10 = AllocateFastOrSlowJSObjectFromMap_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp9});
    tmp11 = UnsafeCast_JSFinalizationRegistry_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp10});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<NativeContext>(CodeStubAssembler::Reference{tmp11, tmp12}, parameter0);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(CodeStubAssembler::Reference{tmp11, tmp13}, tmp6);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp15 = FromConstexpr_int32_constexpr_int32_0(state_, 0);
    tmp16 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp15});
    tmp17 = (TNode<Uint32T>{tmp16});
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp19 = ca_.UncheckedCast<Uint32T>(CodeStubAssembler(state_).UpdateWord32<base::BitField<bool, 0, 1, uint32_t>>(ca_.UncheckedCast<Word32T>(tmp17), ca_.UncheckedCast<Uint32T>(tmp18), true));
    tmp20 = SmiTag_FinalizationRegistryFlags_0(state_, TNode<Uint32T>{tmp19});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp14}, tmp20);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp22 = CodeStubAssembler(state_).LoadReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{tmp11, tmp21});
    tmp23 = Undefined_0(state_);
    tmp24 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp22}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp23});
    ca_.Branch(tmp24, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/finalization-registry.tq", 61});
      CodeStubAssembler(state_).FailAssert("Torque assert 'finalizationRegistry.active_cells == Undefined' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp25;
  TNode<Union<Undefined, WeakCell>> tmp26;
  TNode<Undefined> tmp27;
  TNode<BoolT> tmp28;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp26 = CodeStubAssembler(state_).LoadReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{tmp11, tmp25});
    tmp27 = Undefined_0(state_);
    tmp28 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp26}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp27});
    ca_.Branch(tmp28, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/finalization-registry.tq", 62});
      CodeStubAssembler(state_).FailAssert("Torque assert 'finalizationRegistry.cleared_cells == Undefined' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp29;
  TNode<Object> tmp30;
  TNode<Undefined> tmp31;
  TNode<BoolT> tmp32;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp30 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp11, tmp29});
    tmp31 = Undefined_0(state_);
    tmp32 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp30}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp31});
    ca_.Branch(tmp32, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/finalization-registry.tq", 63});
      CodeStubAssembler(state_).FailAssert("Torque assert 'finalizationRegistry.key_map == Undefined' failed", pos_stack);
    }
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    arguments.PopAndReturn(tmp11);
  }
}

TF_BUILTIN(FinalizationRegistryRegister, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Union<JSReceiver, Symbol, Undefined>> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Union<JSReceiver, Symbol, Undefined>> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Union<JSReceiver, Symbol, Undefined>> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSFinalizationRegistry> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSFinalizationRegistry_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  TNode<Object> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_Object_constexpr_string_0(state_, "FinalizationRegistry.prototype.register");
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIncompatibleMethodReceiver), TNode<Object>{tmp2}, TNode<Object>{parameter1});
  }

  TNode<IntPtrT> tmp3;
  TNode<JSAny> tmp4;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp3});
    compiler::CodeAssemblerLabel label5(&ca_);
    WeakCollectionsBuiltinsAssembler(state_).GotoIfCannotBeHeldWeakly(TNode<JSAny>{tmp4}, &label5);
    ca_.Goto(&block7);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidWeakRefsRegisterTarget));
  }

  TNode<IntPtrT> tmp6;
  TNode<JSAny> tmp7;
  TNode<Union<JSReceiver, Symbol>> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<JSAny> tmp10;
  TNode<BoolT> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp6 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp6});
    tmp8 = UnsafeCast_JSReceiver_OR_Symbol_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp10 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp9});
    tmp11 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp8}, TNode<Object>{tmp10});
    ca_.Branch(tmp11, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kWeakRefsRegisterTargetAndHoldingsMustNotBeSame));
  }

  TNode<IntPtrT> tmp12;
  TNode<JSAny> tmp13;
  TNode<BoolT> tmp14;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp12 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp13 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IsUndefined(TNode<Object>{tmp13});
    ca_.Branch(tmp14, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp15;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp15 = Undefined_0(state_);
    ca_.Goto(&block13, tmp15);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    compiler::CodeAssemblerLabel label16(&ca_);
    WeakCollectionsBuiltinsAssembler(state_).GotoIfCannotBeHeldWeakly(TNode<JSAny>{tmp13}, &label16);
    ca_.Goto(&block16);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block17);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidWeakRefsUnregisterToken), TNode<Object>{tmp13});
  }

  TNode<Union<JSReceiver, Symbol>> tmp17;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp17 = UnsafeCast_JSReceiver_OR_Symbol_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp13});
    ca_.Goto(&block13, tmp17);
  }

  TNode<Union<JSReceiver, Symbol, Undefined>> phi_bb13_10;
  TNode<Map> tmp18;
  TNode<Undefined> tmp19;
  TNode<Undefined> tmp20;
  TNode<Undefined> tmp21;
  TNode<Undefined> tmp22;
  TNode<BoolT> tmp23;
  TNode<BoolT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<HeapObject> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<WeakCell> tmp36;
  TNode<Undefined> tmp37;
  TNode<BoolT> tmp38;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_10);
    tmp18 = GetWeakCellMap_0(state_, TNode<Context>{parameter0});
    tmp19 = Undefined_0(state_);
    tmp20 = Undefined_0(state_);
    tmp21 = Undefined_0(state_);
    tmp22 = Undefined_0(state_);
    tmp23 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp24 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp26 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp25}, TNode<Map>{tmp18}, TNode<BoolT>{tmp23}, TNode<BoolT>{tmp24});
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp26, tmp27}, tmp18);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<JSFinalizationRegistry>(CodeStubAssembler::Reference{tmp26, tmp28}, tmp0);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<JSAny>(CodeStubAssembler::Reference{tmp26, tmp29}, tmp10);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Union<JSReceiver, Symbol, Undefined>>(CodeStubAssembler::Reference{tmp26, tmp30}, tmp8);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Union<JSReceiver, Symbol, Undefined>>(CodeStubAssembler::Reference{tmp26, tmp31}, phi_bb13_10);
    tmp32 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{tmp26, tmp32}, tmp19);
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{tmp26, tmp33}, tmp20);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{tmp26, tmp34}, tmp21);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<Union<Undefined, WeakCell>>(CodeStubAssembler::Reference{tmp26, tmp35}, tmp22);
    tmp36 = TORQUE_CAST(TNode<HeapObject>{tmp26});
    PushCell_0(state_, TNode<JSFinalizationRegistry>{tmp0}, TNode<WeakCell>{tmp36});
    tmp37 = Undefined_0(state_);
    tmp38 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{phi_bb13_10}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp37});
    ca_.Branch(tmp38, &block18, std::vector<compiler::Node*>{phi_bb13_10}, &block19, std::vector<compiler::Node*>{phi_bb13_10});
  }

  TNode<Union<JSReceiver, Symbol, Undefined>> phi_bb18_10;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_10);
    CodeStubAssembler(state_).CallRuntime(Runtime::kJSFinalizationRegistryRegisterWeakCellWithUnregisterToken, parameter0, tmp0, tmp36);
    ca_.Goto(&block19, phi_bb18_10);
  }

  TNode<Union<JSReceiver, Symbol, Undefined>> phi_bb19_10;
  TNode<Undefined> tmp39;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_10);
    tmp39 = Undefined_0(state_);
    arguments.PopAndReturn(tmp39);
  }
}

// https://crsrc.org/c/v8/src/builtins/finalization-registry.tq?l=51&c=32
TNode<JSFinalizationRegistry> UnsafeCast_JSFinalizationRegistry_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSFinalizationRegistry_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<JSFinalizationRegistry> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSFinalizationRegistry>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/finalization-registry.tq?l=59&c=7
TNode<Smi> SmiTag_FinalizationRegistryFlags_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_value) {
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

// https://crsrc.org/c/v8/src/builtins/finalization-registry.tq?l=73&c=32
TNode<JSFinalizationRegistry> Cast_JSFinalizationRegistry_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSFinalizationRegistry> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSFinalizationRegistry_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSFinalizationRegistry>{tmp2};
}

// https://crsrc.org/c/v8/src/builtins/finalization-registry.tq?l=81&c=18
TNode<Union<JSReceiver, Symbol>> UnsafeCast_JSReceiver_OR_Symbol_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSReceiver_OR_Symbol_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<Union<JSReceiver, Symbol>> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<Union<JSReceiver, Symbol>>{tmp1};
}

} // namespace internal
} // namespace v8
