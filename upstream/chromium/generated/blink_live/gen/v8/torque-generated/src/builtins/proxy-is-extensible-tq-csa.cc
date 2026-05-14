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
#include "torque-generated/src/builtins/proxy-is-extensible-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/object-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ProxyIsExtensible, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSProxy> parameter1 = UncheckedParameter<JSProxy>(Descriptor::kProxy);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<JSReceiver, Null>> tmp1;
  TNode<Null> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).PerformStackCheck(TNode<Context>{parameter0});
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = Null_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block9, tmp4);
  }

  TNode<IntPtrT> tmp5;
  TNode<Union<JSReceiver, Null>> tmp6;
  TNode<BoolT> tmp7;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp6 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp5});
    tmp7 = Is_JSReceiver_JSReceiver_OR_Null_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Null>>{tmp6});
    ca_.Goto(&block9, tmp7);
  }

  TNode<BoolT> phi_bb9_3;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3);
    ca_.Branch(phi_bb9_3, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-is-extensible.tq", 19});
      CodeStubAssembler(state_).FailAssert("Torque assert 'proxy.handler == Null || Is<JSReceiver>(proxy.handler)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp8;
  TNode<Union<JSReceiver, Null>> tmp9;
  TNode<JSReceiver> tmp10;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp9 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp8});
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp9}, &label11);
    ca_.Goto(&block10);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block11);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyRevoked), "isExtensible");
  }

  TNode<IntPtrT> tmp12;
  TNode<Union<JSReceiver, Null>> tmp13;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp14;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp13 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp12});
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = GetMethod_2(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp10}, "isExtensible", &label15);
    ca_.Goto(&block14);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block15);
    }
  }

  TNode<JSAny> tmp16;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp16 = ObjectIsExtensibleImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp13});
    CodeStubAssembler(state_).Return(tmp16);
  }

  TNode<JSAny> tmp17;
  TNode<BoolT> tmp18;
  TNode<JSAny> tmp19;
  TNode<BoolT> tmp20;
  TNode<BoolT> tmp21;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp17 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp14}, TNode<JSAny>{tmp10}, TNode<JSAny>{tmp13});
    tmp18 = ToBoolean_0(state_, TNode<JSAny>{tmp17});
    tmp19 = ObjectIsExtensibleImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp13});
    tmp20 = ToBoolean_0(state_, TNode<JSAny>{tmp19});
    tmp21 = CodeStubAssembler(state_).Word32NotEqual(TNode<BoolT>{tmp18}, TNode<BoolT>{tmp20});
    ca_.Branch(tmp21, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  TNode<Boolean> tmp22;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp22 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp20});
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyIsExtensibleInconsistent), TNode<Object>{tmp22});
  }

  TNode<Boolean> tmp23;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp23 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp18});
    CodeStubAssembler(state_).Return(tmp23);
  }
}

} // namespace internal
} // namespace v8
