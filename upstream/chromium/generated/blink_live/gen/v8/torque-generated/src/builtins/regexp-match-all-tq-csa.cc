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
#include "torque-generated/src/builtins/regexp-match-all-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/boolean-tq-csa.h"
#include "torque-generated/src/builtins/builtins-string-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/promise-abstract-operations-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-all-tq-csa.h"
#include "torque-generated/src/builtins/regexp-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-string-iterator-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-tq-csa.h"
#include "torque-generated/src/objects/string-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/regexp-match-all.tq?l=12&c=1
TNode<JSAny> RegExpPrototypeMatchAllImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<NativeContext> p_nativeContext, TNode<JSAny> p_receiver, TNode<JSAny> p_string) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, BoolT, BoolT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<String> tmp1;
  TNode<JSRegExp> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).ThrowIfNotJSReceiver(TNode<Context>{p_context}, TNode<JSAny>{p_receiver}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIncompatibleMethodReceiver), "RegExp.prototype.@@matchAll");
    tmp0 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver});
    tmp1 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<JSAny>{p_string});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSRegExp_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block4);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block5);
    }
  }

  TNode<JSFunction> tmp4;
  TNode<JSReceiver> tmp5;
  TNode<JSReceiver> tmp6;
  TNode<JSAny> tmp7;
  TNode<JSAny> tmp8;
  TNode<String> tmp9;
  TNode<JSReceiver> tmp10;
  TNode<JSAny> tmp11;
  TNode<Number> tmp12;
  TNode<JSReceiver> tmp13;
  TNode<String> tmp14;
  TNode<Smi> tmp15;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<BoolT> tmp18;
  TNode<String> tmp19;
  TNode<String> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<Smi> tmp25;
  TNode<BoolT> tmp26;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = LoadRegExpFunction_0(state_, TNode<NativeContext>{p_nativeContext});
    tmp5 = CodeStubAssembler(state_).SpeciesConstructor(TNode<Context>{p_context}, TNode<JSAny>{tmp0}, TNode<JSReceiver>{tmp4});
    tmp6 = UnsafeCast_Constructor_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp5});
    tmp7 = FromConstexpr_JSAny_constexpr_string_0(state_, "flags");
    tmp8 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<JSAny>{tmp0}, TNode<JSAny>{tmp7});
    tmp9 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp8});
    tmp10 = CodeStubAssembler(state_).Construct(TNode<Context>{p_context}, TNode<JSReceiver>{tmp6}, TNode<JSAny>{tmp0}, TNode<JSAny>{tmp9});
    tmp11 = RegExpBuiltinsAssembler(state_).SlowLoadLastIndex(TNode<Context>{p_context}, TNode<JSAny>{tmp0});
    tmp12 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp11});
    tmp13 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp10});
    RegExpBuiltinsAssembler(state_).SlowStoreLastIndex(TNode<Context>{p_context}, TNode<JSAny>{tmp13}, TNode<JSAny>{tmp12});
    tmp14 = CodeStubAssembler(state_).StringConstant("g");
    tmp15 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = ca_.CallBuiltin<Smi>(Builtin::kStringIndexOf, TNode<Object>(), tmp9, tmp14, tmp15);
    tmp17 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp18 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp16}, TNode<Smi>{tmp17});
    tmp19 = CodeStubAssembler(state_).StringConstant("u");
    tmp20 = CodeStubAssembler(state_).StringConstant("v");
    tmp21 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp22 = ca_.CallBuiltin<Smi>(Builtin::kStringIndexOf, TNode<Object>(), tmp9, tmp19, tmp21);
    tmp23 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp24 = ca_.CallBuiltin<Smi>(Builtin::kStringIndexOf, TNode<Object>(), tmp9, tmp20, tmp23);
    tmp25 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp26 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp22}, TNode<Smi>{tmp25});
    ca_.Branch(tmp26, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp27;
  TNode<String> tmp28;
  TNode<JSAny> tmp29;
  TNode<JSRegExp> tmp30;
  TNode<BoolT> tmp31;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp27 = RegExpSource_0(state_, TNode<JSRegExp>{tmp2});
    tmp28 = FastFlagsGetter_0(state_, TNode<Context>{p_context}, TNode<JSRegExp>{tmp2});
    tmp29 = RegExpCreate_0(state_, TNode<Context>{p_context}, TNode<NativeContext>{p_nativeContext}, TNode<JSAny>{tmp27}, TNode<String>{tmp28});
    tmp30 = UnsafeCast_JSRegExp_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp29});
    tmp31 = IsFastRegExpPermissive_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp30});
    ca_.Branch(tmp31, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match-all.tq", 44});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsFastRegExpPermissive(matcherRegExp)' failed", pos_stack);
    }
  }

  TNode<JSRegExp> tmp32;
  TNode<Smi> tmp33;
  TNode<BoolT> tmp34;
  TNode<BoolT> tmp35;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp32 = UnsafeCast_FastJSRegExp_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp0});
    tmp33 = RegExpBuiltinsAssembler(state_).FastLoadLastIndex(TNode<JSRegExp>{tmp32});
    RegExpBuiltinsAssembler(state_).FastStoreLastIndex(TNode<JSRegExp>{tmp30}, TNode<Smi>{tmp33});
    tmp34 = RegExpBuiltinsAssembler(state_).FastFlagGetter(TNode<JSRegExp>{tmp30}, CastIfEnumClass<JSRegExp::Flag>(JSRegExp::Flag::kGlobal));
    tmp35 = RegExpBuiltinsAssembler(state_).FastFlagGetter(TNode<JSRegExp>{tmp30}, CastIfEnumClass<JSRegExp::Flag>(JSRegExp::Flag::kUnicode));
    ca_.Branch(tmp35, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp36;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp36 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block10, tmp36);
  }

  TNode<BoolT> tmp37;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp37 = RegExpBuiltinsAssembler(state_).FastFlagGetter(TNode<JSRegExp>{tmp30}, CastIfEnumClass<JSRegExp::Flag>(JSRegExp::Flag::kUnicodeSets));
    ca_.Goto(&block10, tmp37);
  }

  TNode<BoolT> phi_bb10_16;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_16);
    ca_.Goto(&block2, tmp29, tmp34, phi_bb10_16);
  }

  TNode<BoolT> tmp38;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp38 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block13, tmp38);
  }

  TNode<Smi> tmp39;
  TNode<BoolT> tmp40;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp39 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp40 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp24}, TNode<Smi>{tmp39});
    ca_.Goto(&block13, tmp40);
  }

  TNode<BoolT> phi_bb13_23;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_23);
    ca_.Goto(&block2, tmp10, tmp18, phi_bb13_23);
  }

  TNode<JSAny> phi_bb2_6;
  TNode<BoolT> phi_bb2_7;
  TNode<BoolT> phi_bb2_8;
  TNode<JSAny> tmp41;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_6, &phi_bb2_7, &phi_bb2_8);
    tmp41 = RegExpMatchAllAssembler(state_).CreateRegExpStringIterator(TNode<NativeContext>{p_nativeContext}, TNode<JSAny>{phi_bb2_6}, TNode<String>{tmp1}, TNode<BoolT>{phi_bb2_7}, TNode<BoolT>{phi_bb2_8});
    ca_.Goto(&block14);
  }

    ca_.Bind(&block14);
  return TNode<JSAny>{tmp41};
}

TF_BUILTIN(RegExpPrototypeMatchAll, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kString);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RegExpPrototypeMatchAllImpl_0(state_, TNode<Context>{parameter0}, TNode<NativeContext>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSAny>{parameter2});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(RegExpStringIteratorPrototypeNext, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSRegExpStringIterator> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSRegExpStringIterator_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  TNode<Object> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_Object_constexpr_string_0(state_, "%RegExpStringIterator%.prototype.next");
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIncompatibleMethodReceiver), TNode<Object>{tmp2}, TNode<Object>{parameter1});
  }

  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<BoolT> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp4 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp3});
    tmp5 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 1, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp4))));
    ca_.Branch(tmp5, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block6);
  }

  TNode<IntPtrT> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<String> tmp9;
  TNode<BoolT> tmp10;
  TNode<BoolT> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp7 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp0, tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp9 = CodeStubAssembler(state_).LoadReference<String>(CodeStubAssembler::Reference{tmp0, tmp8});
    tmp10 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp11 = IsFastRegExpPermissive_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{tmp7});
    ca_.Branch(tmp11, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<JSRegExp> tmp12;
  TNode<Number> tmp13;
  TNode<RegExpMatchInfo> tmp14;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp12 = UnsafeCast_JSRegExp_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp13 = LoadLastIndexAsLength_0(state_, TNode<Context>{parameter0}, TNode<JSRegExp>{tmp12}, true);
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = RegExpPrototypeExecBodyWithoutResultFast_1(state_, TNode<Context>{parameter0}, TNode<JSRegExp>{tmp12}, TNode<String>{tmp9}, TNode<Number>{tmp13}, &label15);
    ca_.Goto(&block14);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block15);
    }
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Goto(&block10, ca_.Uninitialized<Object>());
  }

  TNode<JSArray> tmp16;
  TNode<BoolT> tmp17;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp16 = RegExpBuiltinsAssembler(state_).ConstructNewResultFromMatchInfo(TNode<Context>{parameter0}, TNode<JSRegExp>{tmp12}, TNode<RegExpMatchInfo>{tmp14}, TNode<String>{tmp9}, TNode<Number>{tmp13});
    tmp17 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block13, tmp16, tmp17);
  }

  TNode<JSAny> tmp18;
  TNode<Null> tmp19;
  TNode<BoolT> tmp20;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp18 = RegExpExec_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp7}, TNode<String>{tmp9});
    tmp19 = Null_0(state_);
    tmp20 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp18}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp19});
    ca_.Branch(tmp20, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block10, tmp18);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block13, tmp18, tmp10);
  }

  TNode<Object> phi_bb13_6;
  TNode<BoolT> phi_bb13_7;
  TNode<BoolT> tmp21;
  TNode<BoolT> tmp22;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6, &phi_bb13_7);
    tmp21 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 2, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp4))));
    tmp22 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp21});
    ca_.Branch(tmp22, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp23;
  TNode<Smi> tmp24;
  TNode<BoolT> tmp25;
  TNode<Smi> tmp26;
  TNode<JSAny> tmp27;
  TNode<False> tmp28;
  TNode<JSObject> tmp29;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp24 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp23});
    tmp25 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp26 = ca_.UncheckedCast<Smi>(ca_.BitcastWordToTaggedSigned(CodeStubAssembler(state_).UpdateWord32InWord<base::BitField<bool, 1, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp24)), ca_.UncheckedCast<Uint32T>(tmp25))));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp23}, tmp26);
    tmp27 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{phi_bb13_6});
    tmp28 = False_0(state_);
    tmp29 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp27}, TNode<Boolean>{tmp28});
    CodeStubAssembler(state_).Return(tmp29);
  }

  TNode<BoolT> tmp30;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp30 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 2, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp4))));
    ca_.Branch(tmp30, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match-all.tq", 167});
      CodeStubAssembler(state_).FailAssert("Torque assert 'flags.global' failed", pos_stack);
    }
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Branch(phi_bb13_7, &block22, std::vector<compiler::Node*>{}, &block23, std::vector<compiler::Node*>{});
  }

  TNode<JSArray> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<FixedArrayBase> tmp33;
  TNode<FixedArray> tmp34;
  TNode<Union<HeapObject, TaggedIndex>> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<UintPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<UintPtrT> tmp40;
  TNode<UintPtrT> tmp41;
  TNode<BoolT> tmp42;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp31 = UnsafeCast_JSRegExpResult_0(state_, TNode<Context>{parameter0}, TNode<Object>{phi_bb13_6});
    tmp32 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp33 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp31, tmp32});
    tmp34 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp33});
    std::tie(tmp35, tmp36, tmp37) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp34}).Flatten();
    tmp38 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp39 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp38});
    tmp40 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp39});
    tmp41 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp37});
    tmp42 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp40}, TNode<UintPtrT>{tmp41});
    ca_.Branch(tmp42, &block29, std::vector<compiler::Node*>{}, &block30, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<Union<HeapObject, TaggedIndex>> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<Object> tmp47;
  TNode<String> tmp48;
  TNode<BoolT> tmp49;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp43 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp39});
    tmp44 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp43});
    std::tie(tmp45, tmp46) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp35}, TNode<IntPtrT>{tmp44}).Flatten();
    tmp47 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp45, tmp46});
    tmp48 = UnsafeCast_String_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp47});
    tmp49 = IsFastRegExpPermissive_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{tmp7});
    ca_.Branch(tmp49, &block33, std::vector<compiler::Node*>{}, &block34, std::vector<compiler::Node*>{});
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match-all.tq", 176});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsFastRegExpPermissive(iteratingRegExp)' failed", pos_stack);
    }
  }

  TNode<JSRegExp> tmp50;
  TNode<String> tmp51;
  TNode<BoolT> tmp52;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp50 = UnsafeCast_JSRegExp_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp51 = kEmptyString_0(state_);
    tmp52 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp48}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp51});
    ca_.Branch(tmp52, &block35, std::vector<compiler::Node*>{}, &block36, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp53;
  TNode<BoolT> tmp54;
  TNode<Smi> tmp55;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp53 = RegExpBuiltinsAssembler(state_).FastLoadLastIndex(TNode<JSRegExp>{tmp50});
    tmp54 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 3, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp4))));
    tmp55 = RegExpBuiltinsAssembler(state_).AdvanceStringIndexFast(TNode<String>{tmp9}, TNode<Smi>{tmp53}, TNode<BoolT>{tmp54});
    RegExpBuiltinsAssembler(state_).FastStoreLastIndex(TNode<JSRegExp>{tmp50}, TNode<Smi>{tmp55});
    ca_.Goto(&block36);
  }

  TNode<False> tmp56;
  TNode<JSObject> tmp57;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp56 = False_0(state_);
    tmp57 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp31}, TNode<Boolean>{tmp56});
    CodeStubAssembler(state_).Return(tmp57);
  }

  TNode<BoolT> tmp58;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp58 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb13_7});
    ca_.Branch(tmp58, &block37, std::vector<compiler::Node*>{}, &block38, std::vector<compiler::Node*>{});
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match-all.tq", 194});
      CodeStubAssembler(state_).FailAssert("Torque assert '!isFastRegExp' failed", pos_stack);
    }
  }

  TNode<JSAny> tmp59;
  TNode<Smi> tmp60;
  TNode<JSAny> tmp61;
  TNode<String> tmp62;
  TNode<String> tmp63;
  TNode<BoolT> tmp64;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp59 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{phi_bb13_6});
    tmp60 = SmiConstant_0(state_, IntegerLiteral(false, 0x0ull));
    tmp61 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp59}, TNode<JSAny>{tmp60});
    tmp62 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp61});
    tmp63 = kEmptyString_0(state_);
    tmp64 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp62}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp63});
    ca_.Branch(tmp64, &block39, std::vector<compiler::Node*>{}, &block40, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp65;
  TNode<Number> tmp66;
  TNode<BoolT> tmp67;
  TNode<Number> tmp68;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp65 = RegExpBuiltinsAssembler(state_).SlowLoadLastIndex(TNode<Context>{parameter0}, TNode<JSAny>{tmp7});
    tmp66 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp65});
    tmp67 = ca_.UncheckedCast<BoolT>(CodeStubAssembler(state_).DecodeWord32FromWord<base::BitField<bool, 3, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp4))));
    tmp68 = RegExpBuiltinsAssembler(state_).AdvanceStringIndexSlow(TNode<String>{tmp9}, TNode<Number>{tmp66}, TNode<BoolT>{tmp67});
    RegExpBuiltinsAssembler(state_).SlowStoreLastIndex(TNode<Context>{parameter0}, TNode<JSAny>{tmp7}, TNode<JSAny>{tmp68});
    ca_.Goto(&block40);
  }

  TNode<False> tmp69;
  TNode<JSObject> tmp70;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp69 = False_0(state_);
    tmp70 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp59}, TNode<Boolean>{tmp69});
    CodeStubAssembler(state_).Return(tmp70);
  }

  TNode<Object> phi_bb10_6;
  TNode<IntPtrT> tmp71;
  TNode<Smi> tmp72;
  TNode<BoolT> tmp73;
  TNode<Smi> tmp74;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_6);
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp72 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp71});
    tmp73 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp74 = ca_.UncheckedCast<Smi>(ca_.BitcastWordToTaggedSigned(CodeStubAssembler(state_).UpdateWord32InWord<base::BitField<bool, 1, 1, uintptr_t>>(ca_.UncheckedCast<WordT>(ca_.BitcastTaggedToWordForTagAndSmiBits(tmp72)), ca_.UncheckedCast<Uint32T>(tmp73))));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp71}, tmp74);
    ca_.Goto(&block6);
  }

  TNode<Undefined> tmp75;
  TNode<True> tmp76;
  TNode<JSObject> tmp77;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp75 = Undefined_0(state_);
    tmp76 = True_0(state_);
    tmp77 = CodeStubAssembler(state_).AllocateJSIteratorResult(TNode<Context>{parameter0}, TNode<JSAny>{tmp75}, TNode<Boolean>{tmp76});
    CodeStubAssembler(state_).Return(tmp77);
  }
}

// https://crsrc.org/c/v8/src/builtins/regexp-match-all.tq?l=43&c=29
TNode<JSRegExp> UnsafeCast_JSRegExp_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSRegExp_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSRegExp> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSRegExp>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/regexp-match-all.tq?l=48&c=26
TNode<JSRegExp> UnsafeCast_FastJSRegExp_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_FastJSRegExp_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSRegExp> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSRegExp>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/regexp-match-all.tq?l=119&c=20
TNode<JSRegExpStringIterator> Cast_JSRegExpStringIterator_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSRegExpStringIterator> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSRegExpStringIterator_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSRegExpStringIterator>{tmp2};
}

// https://crsrc.org/c/v8/src/builtins/regexp-match-all.tq?l=170&c=23
TNode<JSArray> UnsafeCast_JSRegExpResult_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSRegExpResult_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSArray> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSArray>{tmp1};
}

} // namespace internal
} // namespace v8
