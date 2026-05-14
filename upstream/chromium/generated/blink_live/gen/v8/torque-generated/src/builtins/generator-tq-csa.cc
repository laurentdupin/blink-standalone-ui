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
#include "torque-generated/src/builtins/generator-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/generator-tq-csa.h"
#include "torque-generated/src/objects/js-generator-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(GeneratorPrototypeNextLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kGenerator);
  USE(parameter2);
  TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> parameter3 = UncheckedParameter<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>>(Descriptor::kException);
  USE(parameter3);
  TNode<JSAny> parameter4 = UncheckedParameter<JSAny>(Descriptor::kResult);
  USE(parameter4);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSGeneratorObject> tmp0;
  TNode<TheHole> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSGeneratorObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = Cast_TheHole_0(state_, TNode<Object>{parameter3}, &label2);
    ca_.Goto(&block3);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block4);
    }
  }

  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp4 = CodeStubAssembler(state_).SmiConstant(JSGeneratorObject::kGeneratorClosed);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp3}, tmp4);
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrow, parameter0, ca_.UncheckedCast<JSAny>(parameter3));
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp6 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp5});
    tmp7 = CodeStubAssembler(state_).SmiConstant(JSGeneratorObject::kGeneratorExecuting);
    tmp8 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp6}, TNode<Smi>{tmp7});
    ca_.Branch(tmp8, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp9;
  TNode<Smi> tmp10;
  TNode<True> tmp11;
  TNode<JSObject> tmp12;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp10 = CodeStubAssembler(state_).SmiConstant(JSGeneratorObject::kGeneratorClosed);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp9}, tmp10);
    tmp11 = True_0(state_);
    tmp12 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{parameter4}, TNode<Boolean>{tmp11});
    CodeStubAssembler(state_).Return(tmp12);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).Return(parameter4);
  }
}

// https://crsrc.org/c/v8/src/builtins/generator.tq?l=21&c=15
TNode<JSGeneratorObject> UnsafeCast_JSGeneratorObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSGeneratorObject_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSGeneratorObject> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSGeneratorObject>{tmp1};
}

} // namespace internal
} // namespace v8
