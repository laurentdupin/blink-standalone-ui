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
#include "torque-generated/src/builtins/proxy-has-property-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-has-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/js-proxy-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ProxyHasProperty, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSProxy> parameter1 = UncheckedParameter<JSProxy>(Descriptor::kProxy);
  USE(parameter1);
  TNode<Union<String, Symbol>> parameter2 = UncheckedParameter<Union<String, Symbol>>(Descriptor::kName);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Is_JSProxy_JSProxy_0(state_, TNode<Context>{parameter0}, TNode<JSProxy>{parameter1});
    ca_.Branch(tmp0, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-has-property.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<JSProxy>(proxy)' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp1;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).PerformStackCheck(TNode<Context>{parameter0});
    tmp1 = Is_Name_PropertyKey_0(state_, TNode<Context>{parameter0}, TNode<Union<String, Symbol>>{parameter2});
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-has-property.tq", 18});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<Name>(name)' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp2;
  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = IsPrivateSymbol_0(state_, TNode<HeapObject>{parameter2});
    tmp3 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp2});
    ca_.Branch(tmp3, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-has-property.tq", 19});
      CodeStubAssembler(state_).FailAssert("Torque assert '!IsPrivateSymbol(name)' failed", pos_stack);
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
    ca_.Branch(tmp7, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp8;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block15, tmp8);
  }

  TNode<IntPtrT> tmp9;
  TNode<Union<JSReceiver, Null>> tmp10;
  TNode<BoolT> tmp11;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp10 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp9});
    tmp11 = Is_JSReceiver_JSReceiver_OR_Null_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Null>>{tmp10});
    ca_.Goto(&block15, tmp11);
  }

  TNode<BoolT> phi_bb15_4;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_4);
    ca_.Branch(phi_bb15_4, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-has-property.tq", 25});
      CodeStubAssembler(state_).FailAssert("Torque assert 'proxy.handler == Null || Is<JSReceiver>(proxy.handler)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp12;
  TNode<Union<JSReceiver, Null>> tmp13;
  TNode<JSReceiver> tmp14;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp13 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp12});
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp13}, &label15);
    ca_.Goto(&block16);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block17);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyRevoked), "has");
  }

  TNode<IntPtrT> tmp16;
  TNode<Union<JSReceiver, Null>> tmp17;
  TNode<JSReceiver> tmp18;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp17 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp16});
    compiler::CodeAssemblerLabel label19(&ca_);
    tmp18 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp17}, &label19);
    ca_.Goto(&block20);
    if (label19.is_used()) {
      ca_.Bind(&label19);
      ca_.Goto(&block21);
    }
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/proxy-has-property.tq:30:61");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp20;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    compiler::CodeAssemblerLabel label21(&ca_);
    tmp20 = GetMethod_2(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp14}, "has", &label21);
    ca_.Goto(&block24);
    if (label21.is_used()) {
      ca_.Bind(&label21);
      ca_.Goto(&block25);
    }
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
   CodeStubAssembler(state_).TailCallBuiltin(Builtin::kHasProperty, parameter0, tmp18, parameter2);
  }

  TNode<JSAny> tmp22;
  TNode<BoolT> tmp23;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp22 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp20}, TNode<JSAny>{tmp14}, TNode<JSAny>{tmp18}, TNode<JSAny>{parameter2});
    tmp23 = ToBoolean_0(state_, TNode<JSAny>{tmp22});
    ca_.Branch(tmp23, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  TNode<True> tmp24;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp24 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp24);
  }

  TNode<False> tmp25;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    ProxiesCodeStubAssembler(state_).CheckHasTrapResult(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp18}, TNode<JSProxy>{parameter1}, TNode<Name>{parameter2});
    tmp25 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp25);
  }
}

// https://crsrc.org/c/v8/src/builtins/proxy-has-property.tq?l=13&c=10
TNode<BoolT> Is_JSProxy_JSProxy_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSProxy> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSProxy> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSProxy_0(state_, TNode<HeapObject>{p_o}, &label1);
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
