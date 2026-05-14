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
#include "torque-generated/src/builtins/proxy-get-prototype-of-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/iterator-helpers-tq-csa.h"
#include "torque-generated/src/builtins/object-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ProxyGetPrototypeOf, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSProxy> parameter1 = UncheckedParameter<JSProxy>(Descriptor::kProxy);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    ca_.Branch(tmp3, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp4;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block11, tmp4);
  }

  TNode<IntPtrT> tmp5;
  TNode<Union<JSReceiver, Null>> tmp6;
  TNode<BoolT> tmp7;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp6 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp5});
    tmp7 = Is_JSReceiver_JSReceiver_OR_Null_0(state_, TNode<Context>{parameter0}, TNode<Union<JSReceiver, Null>>{tmp6});
    ca_.Goto(&block11, tmp7);
  }

  TNode<BoolT> phi_bb11_3;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_3);
    ca_.Branch(phi_bb11_3, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-get-prototype-of.tq", 19});
      CodeStubAssembler(state_).FailAssert("Torque assert 'proxy.handler == Null || Is<JSReceiver>(proxy.handler)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp8;
  TNode<Union<JSReceiver, Null>> tmp9;
  TNode<JSReceiver> tmp10;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp9 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp8});
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_JSReceiver_0(state_, TNode<HeapObject>{tmp9}, &label11);
    ca_.Goto(&block12);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block13);
    }
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyRevoked), "getPrototypeOf");
  }

  TNode<IntPtrT> tmp12;
  TNode<Union<JSReceiver, Null>> tmp13;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp14;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp13 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Null>>(CodeStubAssembler::Reference{parameter1, tmp12});
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = GetMethod_2(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp10}, "getPrototypeOf", &label15);
    ca_.Goto(&block16);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block17);
    }
  }

  TNode<JSAny> tmp16;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp16 = ObjectGetPrototypeOfImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp13});
    CodeStubAssembler(state_).Return(tmp16);
  }

  TNode<JSAny> tmp17;
  TNode<BoolT> tmp18;
  TNode<BoolT> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp17 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp14}, TNode<JSAny>{tmp10}, TNode<JSAny>{tmp13});
    tmp18 = Is_JSReceiver_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp17});
    tmp19 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp18});
    ca_.Branch(tmp19, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<Null> tmp20;
  TNode<BoolT> tmp21;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp20 = Null_0(state_);
    tmp21 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp17}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp20});
    ca_.Goto(&block22, tmp21);
  }

  TNode<BoolT> tmp22;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp22 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block22, tmp22);
  }

  TNode<BoolT> phi_bb22_7;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7);
    ca_.Branch(phi_bb22_7, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyGetPrototypeOfInvalid));
  }

  TNode<JSAny> tmp23;
  TNode<True> tmp24;
  TNode<BoolT> tmp25;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp23 = ObjectIsExtensibleImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp13});
    tmp24 = True_0(state_);
    tmp25 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp23}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp24});
    ca_.Branch(tmp25, &block25, std::vector<compiler::Node*>{}, &block26, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp26;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp26 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block27, tmp26);
  }

  TNode<False> tmp27;
  TNode<BoolT> tmp28;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp27 = False_0(state_);
    tmp28 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp23}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp27});
    ca_.Goto(&block27, tmp28);
  }

  TNode<BoolT> phi_bb27_8;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_8);
    ca_.Branch(phi_bb27_8, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/proxy-get-prototype-of.tq", 43});
      CodeStubAssembler(state_).FailAssert("Torque assert 'extensibleTarget == True || extensibleTarget == False' failed", pos_stack);
    }
  }

  TNode<True> tmp29;
  TNode<BoolT> tmp30;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp29 = True_0(state_);
    tmp30 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp23}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp29});
    ca_.Branch(tmp30, &block28, std::vector<compiler::Node*>{}, &block29, std::vector<compiler::Node*>{});
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    CodeStubAssembler(state_).Return(tmp17);
  }

  TNode<JSAny> tmp31;
  TNode<BoolT> tmp32;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp31 = ObjectGetPrototypeOfImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp13});
    tmp32 = SameValue_0(state_, TNode<Union<BigInt, Context, FixedArrayBase, FunctionTemplateInfo, HeapNumber, Hole, JSReceiver, Map, Oddball, Smi, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp31}, TNode<Union<BigInt, Context, FixedArrayBase, FunctionTemplateInfo, HeapNumber, Hole, JSReceiver, Map, Oddball, Smi, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp17});
    ca_.Branch(tmp32, &block30, std::vector<compiler::Node*>{}, &block31, std::vector<compiler::Node*>{});
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    CodeStubAssembler(state_).Return(tmp17);
  }

  if (block31.is_used()) {
    ca_.Bind(&block31);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kProxyGetPrototypeOfNonExtensible));
  }
}

} // namespace internal
} // namespace v8
