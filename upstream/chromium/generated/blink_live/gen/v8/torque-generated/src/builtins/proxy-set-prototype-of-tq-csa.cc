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
#include "torque-generated/src/builtins/proxy-set-prototype-of-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/object-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ProxySetPrototypeOf, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSProxy> parameter1 = UncheckedParameter<JSProxy>(Descriptor::kProxy);
  USE(parameter1);
  TNode<Union<JSReceiver, Null>> parameter2 = UncheckedParameter<Union<JSReceiver, Null>>(Descriptor::kProto);
  USE(parameter2);
  TNode<Boolean> parameter3 = UncheckedParameter<Boolean>(Descriptor::kDoThrow);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Null> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).PerformStackCheck(TNode<Context>{parameter0});
    tmp0 = Null_0(state_);
    tmp1 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp0});
    ca_.Branch(tmp1, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp2;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block9, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp3 = Is_JSReceiver_JSReceiver_OR_Null_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Null>>{parameter2});
    ca_.Goto(&block9, tmp3);
  }

  TNode<BoolT> phi_bb9_5;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5);
    ca_.Branch(phi_bb9_5, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-set-prototype-of.tq", 18});
      CodeStubAssembler(state_).FailAssert("Torque assert 'proto == Null || Is<JSReceiver>(proto)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp4;
  TNode<Union<JSReceiver, Null>> tmp5;
  TNode<Null> tmp6;
  TNode<BoolT> tmp7;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp5 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp4});
    tmp6 = Null_0(state_);
    tmp7 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp5}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp6});
    ca_.Branch(tmp7, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp8;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block14, tmp8);
  }

  TNode<IntPtrT> tmp9;
  TNode<Union<JSReceiver, Null>> tmp10;
  TNode<BoolT> tmp11;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp10 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp9});
    tmp11 = Is_JSReceiver_JSReceiver_OR_Null_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Null>>{tmp10});
    ca_.Goto(&block14, tmp11);
  }

  TNode<BoolT> phi_bb14_5;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_5);
    ca_.Branch(phi_bb14_5, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-set-prototype-of.tq", 23});
      CodeStubAssembler(state_).FailAssert("Torque assert 'proxy.handler == Null || Is<JSReceiver>(proxy.handler)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp12;
  TNode<Union<JSReceiver, Null>> tmp13;
  TNode<JSReceiver> tmp14;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp13 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp12});
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp13}, &label15);
    ca_.Goto(&block15);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyRevoked), "setPrototypeOf");
  }

  TNode<IntPtrT> tmp16;
  TNode<Union<JSReceiver, Null>> tmp17;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp18;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp17 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp16});
    compiler::CodeAssemblerLabel label19(&ca_);
    tmp18 = GetMethod_2(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp14}, "setPrototypeOf", &label19);
    ca_.Goto(&block19);
    if (label19.is_used()) {
      ca_.Bind(&label19);
      ca_.Goto(&block20);
    }
  }

  TNode<True> tmp20;
  TNode<BoolT> tmp21;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp20 = True_0(state_);
    tmp21 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter3}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp20});
    ca_.Branch(tmp21, &block34, std::vector<compiler::Node*>{}, &block35, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp22;
  TNode<BoolT> tmp23;
  TNode<BoolT> tmp24;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp22 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp18}, TNode<JSAny>{tmp14}, TNode<JSAny>{tmp17}, TNode<JSAny>{parameter2});
    tmp23 = ToBoolean_0(state_, TNode<JSAny>{tmp22});
    tmp24 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp23});
    ca_.Branch(tmp24, &block21, std::vector<compiler::Node*>{}, &block22, std::vector<compiler::Node*>{});
  }

  TNode<True> tmp25;
  TNode<BoolT> tmp26;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp25 = True_0(state_);
    tmp26 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter3}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp25});
    ca_.Branch(tmp26, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyTrapReturnedFalsishFor), "setPrototypeOf");
  }

  TNode<False> tmp27;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp27 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp27);
  }

  TNode<JSAny> tmp28;
  TNode<True> tmp29;
  TNode<BoolT> tmp30;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp28 = ObjectIsExtensibleImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp17});
    tmp29 = True_0(state_);
    tmp30 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp28}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp29});
    ca_.Branch(tmp30, &block27, std::vector<compiler::Node*>{}, &block28, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp31;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp31 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block29, tmp31);
  }

  TNode<False> tmp32;
  TNode<BoolT> tmp33;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp32 = False_0(state_);
    tmp33 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp28}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp32});
    ca_.Goto(&block29, tmp33);
  }

  TNode<BoolT> phi_bb29_10;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_10);
    ca_.Branch(phi_bb29_10, &block25, std::vector<compiler::Node*>{}, &block26, std::vector<compiler::Node*>{});
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-set-prototype-of.tq", 51});
      CodeStubAssembler(state_).FailAssert("Torque assert 'extensibleTarget == True || extensibleTarget == False' failed", pos_stack);
    }
  }

  TNode<True> tmp34;
  TNode<BoolT> tmp35;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp34 = True_0(state_);
    tmp35 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp28}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp34});
    ca_.Branch(tmp35, &block30, std::vector<compiler::Node*>{}, &block31, std::vector<compiler::Node*>{});
  }

  TNode<True> tmp36;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp36 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp36);
  }

  TNode<JSAny> tmp37;
  TNode<BoolT> tmp38;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp37 = ObjectGetPrototypeOfImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp17});
    tmp38 = SameValue_0(state_, TNode<Union<BigInt, Context, FixedArrayBase, FunctionTemplateInfo, HeapNumber, Hole, JSReceiver, Map, Oddball, Smi, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2}, TNode<Union<BigInt, Context, FixedArrayBase, FunctionTemplateInfo, HeapNumber, Hole, JSReceiver, Map, Oddball, Smi, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp37});
    ca_.Branch(tmp38, &block32, std::vector<compiler::Node*>{}, &block33, std::vector<compiler::Node*>{});
  }

  TNode<True> tmp39;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp39 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp39);
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxySetPrototypeOfNonExtensible));
  }

  TNode<JSAny> tmp40;
  if (block34.is_used()) {
    ca_.Bind(&block34);
    tmp40 = ObjectSetPrototypeOfThrow_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp17}, TNode<Union<JSReceiver, Null>>{parameter2});
    CodeStubAssembler(state_).Return(tmp40);
  }

  TNode<JSAny> tmp41;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp41 = ObjectSetPrototypeOfDontThrow_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp17}, TNode<Union<JSReceiver, Null>>{parameter2});
    CodeStubAssembler(state_).Return(tmp41);
  }
}

} // namespace internal
} // namespace v8
