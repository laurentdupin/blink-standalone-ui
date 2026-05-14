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
#include "torque-generated/src/builtins/proxy-get-property-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-get-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ProxyGetProperty, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSProxy> parameter1 = UncheckedParameter<JSProxy>(Descriptor::kProxy);
  USE(parameter1);
  TNode<Union<String, Symbol>> parameter2 = UncheckedParameter<Union<String, Symbol>>(Descriptor::kName);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kReceiverValue);
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedParameter<Smi>(Descriptor::kOnNonExistent);
  USE(parameter4);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
      pos_stack.push_back({"src/builtins/proxy-get-property.tq", 19});
      CodeStubAssembler(state_).FailAssert("Torque assert 'TaggedIsNotSmi(name)' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp1;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp1 = Is_Name_PropertyKey_0(state_, TNode<Context>{parameter0}, TNode<Union<String, Symbol>>{parameter2});
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-get-property.tq", 20});
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
      pos_stack.push_back({"src/builtins/proxy-get-property.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert '!IsPrivateSymbol(name)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp4;
  TNode<Union<JSReceiver, Null>> tmp5;
  TNode<Null> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp5 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp4});
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Null_0(state_, TNode<HeapObject>{tmp5}, &label7);
    ca_.Goto(&block9);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block10);
    }
  }

  TNode<IntPtrT> tmp8;
  TNode<Union<JSReceiver, Null>> tmp9;
  TNode<JSReceiver> tmp10;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp9 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp8});
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp9}, &label11);
    ca_.Goto(&block13);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block14);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyRevoked), "get");
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/proxy-get-property.tq:37:59");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> tmp12;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp13;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp12 = CodeStubAssembler(state_).GetStringConstant();
    compiler::CodeAssemblerLabel label14(&ca_);
    tmp13 = GetInterestingMethod_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{ca_.UncheckedCast<JSReceiver>(tmp5)}, TNode<String>{tmp12}, &label14);
    ca_.Goto(&block17);
    if (label14.is_used()) {
      ca_.Bind(&label14);
      ca_.Goto(&block18);
    }
  }

  TNode<JSAny> tmp15;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp15 = ca_.CallBuiltin<JSAny>(Builtin::kGetPropertyWithReceiver, parameter0, tmp10, parameter2, parameter3, parameter4);
    CodeStubAssembler(state_).Return(tmp15);
  }

  TNode<JSAny> tmp16;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp16 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp13}, TNode<JSAny>{ca_.UncheckedCast<JSReceiver>(tmp5)}, TNode<JSAny>{tmp10}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter3});
    ProxiesCodeStubAssembler(state_).CheckGetSetTrapResult(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp10}, TNode<JSProxy>{parameter1}, TNode<Name>{parameter2}, TNode<Object>{tmp16}, JSProxy::AccessKind::kGet);
    CodeStubAssembler(state_).Return(tmp16);
  }
}

} // namespace internal
} // namespace v8
