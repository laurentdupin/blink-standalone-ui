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
#include "torque-generated/src/builtins/proxy-set-property-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/boolean-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-set-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/name-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/proxy-set-property.tq?l=12&c=1
void CallThrowTypeErrorIfStrict_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, MessageTemplate p_message) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Null> tmp1;
  TNode<Null> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiConstant(p_message);
    tmp1 = Null_0(state_);
    tmp2 = Null_0(state_);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowTypeErrorIfStrict, p_context, tmp0, tmp1, tmp2);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TF_BUILTIN(ProxySetProperty, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSProxy> parameter1 = UncheckedParameter<JSProxy>(Descriptor::kProxy);
  USE(parameter1);
  TNode<Union<String, Symbol>> parameter2 = UncheckedParameter<Union<String, Symbol>>(Descriptor::kName);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  TNode<JSAny> parameter4 = UncheckedParameter<JSAny>(Descriptor::kReceiverValue);
  USE(parameter4);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).PerformStackCheck(TNode<Context>{parameter0});
    tmp0 = CodeStubAssembler(state_).TaggedIsNotSmi(TNode<Object>{parameter2});
    ca_.Branch(tmp0, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-set-property.tq", 25});
      CodeStubAssembler(state_).FailAssert("Torque assert 'TaggedIsNotSmi(name)' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp1;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp1 = Is_Name_AnyName_0(state_, TNode<Context>{parameter0}, TNode<Union<String, Symbol>>{parameter2});
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-set-property.tq", 26});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<Name>(name)' failed", pos_stack);
    }
  }

  TNode<Symbol> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_PrivateSymbol_1(state_, TNode<HeapObject>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  TNode<IntPtrT> tmp4;
  TNode<Union<JSReceiver, Null>> tmp5;
  TNode<Null> tmp6;
  TNode<BoolT> tmp7;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp5 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp4});
    tmp6 = Null_0(state_);
    tmp7 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp5}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp6});
    ca_.Branch(tmp7, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    CallThrowTypeErrorIfStrict_0(state_, TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyPrivate));
    tmp8 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp8);
  }

  TNode<BoolT> tmp9;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block17, tmp9);
  }

  TNode<IntPtrT> tmp10;
  TNode<Union<JSReceiver, Null>> tmp11;
  TNode<BoolT> tmp12;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp11 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp10});
    tmp12 = Is_JSReceiver_JSReceiver_OR_Null_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Null>>{tmp11});
    ca_.Goto(&block17, tmp12);
  }

  TNode<BoolT> phi_bb17_7;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    ca_.Branch(phi_bb17_7, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-set-property.tq", 43});
      CodeStubAssembler(state_).FailAssert("Torque assert 'proxy.handler == Null || Is<JSReceiver>(proxy.handler)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp13;
  TNode<Union<JSReceiver, Null>> tmp14;
  TNode<JSReceiver> tmp15;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp14 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp13});
    compiler::CodeAssemblerLabel label16(&ca_);
    tmp15 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp14}, &label16);
    ca_.Goto(&block18);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block19);
    }
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyRevoked), "set");
  }

  TNode<IntPtrT> tmp17;
  TNode<Union<JSReceiver, Null>> tmp18;
  TNode<JSReceiver> tmp19;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp20;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp18 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp17});
    tmp19 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp18});
    compiler::CodeAssemblerLabel label21(&ca_);
    tmp20 = GetMethod_2(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp15}, "set", &label21);
    ca_.Goto(&block22);
    if (label21.is_used()) {
      ca_.Bind(&label21);
      ca_.Goto(&block23);
    }
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    CodeStubAssembler(state_).CallRuntime(Runtime::kSetPropertyWithReceiver, parameter0, tmp19, parameter2, parameter3, parameter4);
    CodeStubAssembler(state_).Return(parameter3);
  }

  TNode<JSAny> tmp22;
  TNode<BoolT> tmp23;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp22 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp20}, TNode<JSAny>{tmp15}, TNode<JSAny>{tmp19}, TNode<JSAny>{ca_.UncheckedCast<Union<String, Symbol>>(parameter2)}, TNode<JSAny>{parameter3}, TNode<JSAny>{parameter4});
    tmp23 = ToBoolean_0(state_, TNode<JSAny>{tmp22});
    ca_.Branch(tmp23, &block24, std::vector<compiler::Node*>{}, &block25, std::vector<compiler::Node*>{});
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    ProxiesCodeStubAssembler(state_).CheckGetSetTrapResult(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp19}, TNode<JSProxy>{parameter1}, TNode<Name>{parameter2}, TNode<Object>{parameter3}, JSProxy::AccessKind::kSet);
    CodeStubAssembler(state_).Return(parameter3);
  }

  TNode<Smi> tmp24;
  TNode<Object> tmp25;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp24 = CodeStubAssembler(state_).SmiConstant(CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyTrapReturnedFalsishFor));
    tmp25 = FromConstexpr_Object_constexpr_string_0(state_, "set");
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowTypeErrorIfStrict, parameter0, tmp24, tmp25, parameter2);
    CodeStubAssembler(state_).Return(parameter3);
  }
}

// https://crsrc.org/c/v8/src/builtins/proxy-set-property.tq?l=26&c=10
TNode<BoolT> Is_Name_AnyName_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Union<String, Symbol>> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Name> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_Name_0(state_, TNode<HeapObject>{p_o}, &label1);
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
