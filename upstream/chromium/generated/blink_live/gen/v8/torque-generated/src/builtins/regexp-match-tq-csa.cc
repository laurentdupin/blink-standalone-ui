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
#include "torque-generated/src/builtins/regexp-match-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/boolean-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/growable-fixed-array-tq-csa.h"
#include "torque-generated/src/builtins/regexp-exec-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-all-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-tq-csa.h"
#include "torque-generated/src/builtins/regexp-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-tq-csa.h"
#include "torque-generated/src/objects/string-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/regexp-match.tq?l=24&c=1
TNode<JSAny> RegExpPrototypeMatchBody_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_regexp, TNode<String> p_string, bool p_isFastPath) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, String> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block46(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block48(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Union<JSArray, Null>> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block61(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    if ((p_isFastPath)) {
      ca_.Goto(&block2);
    } else {
      ca_.Goto(&block3);
    }
  }

  TNode<BoolT> tmp0;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp0 = Is_FastJSRegExp_JSReceiver_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp});
    ca_.Branch(tmp0, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match.tq", 28});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<FastJSRegExp>(regexp)' failed", pos_stack);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block4);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4);
  }

  TNode<String> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = CodeStubAssembler(state_).StringConstant("");
    if ((p_isFastPath)) {
      ca_.Goto(&block7);
    } else {
      ca_.Goto(&block8);
    }
  }

  TNode<JSRegExp> tmp2;
  TNode<BoolT> tmp3;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp2 = UnsafeCast_FastJSRegExp_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp});
    tmp3 = RegExpBuiltinsAssembler(state_).FastFlagGetter(TNode<JSRegExp>{tmp2}, CastIfEnumClass<JSRegExp::Flag>(JSRegExp::Flag::kGlobal));
    ca_.Goto(&block9, tmp3, tmp1);
  }

  TNode<JSAny> tmp4;
  TNode<JSAny> tmp5;
  TNode<String> tmp6;
  TNode<String> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<BoolT> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp4 = FromConstexpr_JSAny_constexpr_string_0(state_, "flags");
    tmp5 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<JSAny>{p_regexp}, TNode<JSAny>{tmp4});
    tmp6 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp5});
    tmp7 = CodeStubAssembler(state_).StringConstant("g");
    tmp8 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp9 = ca_.CallBuiltin<Smi>(Builtin::kStringIndexOf, TNode<Object>(), tmp6, tmp7, tmp8);
    tmp10 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp11 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp9}, TNode<Smi>{tmp10});
    ca_.Goto(&block9, tmp11, tmp6);
  }

  TNode<BoolT> phi_bb9_3;
  TNode<String> phi_bb9_4;
  TNode<BoolT> tmp12;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3, &phi_bb9_4);
    tmp12 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb9_3});
    ca_.Branch(tmp12, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp13;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp13 = FromConstexpr_bool_constexpr_bool_0(state_, p_isFastPath);
    ca_.Branch(tmp13, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp14;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp14 = RegExpPrototypeExecBodyFast_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp}, TNode<String>{p_string});
    ca_.Goto(&block14, tmp14);
  }

  TNode<JSAny> tmp15;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp15 = RegExpExec_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp}, TNode<String>{p_string});
    ca_.Goto(&block14, tmp15);
  }

  TNode<JSAny> phi_bb14_5;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_5);
    ca_.Goto(&block1, phi_bb14_5);
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Branch(phi_bb9_3, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match.tq", 51});
      CodeStubAssembler(state_).FailAssert("Torque assert 'isGlobal' failed", pos_stack);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    if ((p_isFastPath)) {
      ca_.Goto(&block18);
    } else {
      ca_.Goto(&block19);
    }
  }

  TNode<JSRegExp> tmp16;
  TNode<RegExpData> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<Smi> tmp19;
  TNode<Number> tmp20;
  TNode<BoolT> tmp21;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp16 = UnsafeCast_JSRegExp_0(state_, TNode<Context>{p_context}, TNode<Object>{p_regexp});
    tmp17 = RegExpBuiltinsAssembler(state_).LoadRegExpDataFromObject(TNode<HeapObject>{tmp16}, JSRegExp::kDataOffset);
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp19 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp17, tmp18});
    tmp20 = FromConstexpr_Number_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(static_cast<uint8_t>(RegExpData::Type::ATOM)));
    tmp21 = IsNumberEqual_0(state_, TNode<Number>{tmp19}, TNode<Number>{tmp20});
    ca_.Branch(tmp21, &block21, std::vector<compiler::Node*>{}, &block22, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp22;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp22 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kRegExpMatchGlobalAtom, p_context, tmp16, p_string, tmp17)); 
    ca_.Goto(&block1, tmp22);
  }

  TNode<JSAny> tmp23;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp23 = RegExpBuiltinsAssembler(state_).RegExpMatchGlobal(TNode<Context>{p_context}, TNode<JSRegExp>{tmp16}, TNode<String>{p_string}, TNode<RegExpData>{tmp17});
    ca_.Goto(&block1, tmp23);
  }

  TNode<BoolT> tmp24;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp24 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprBoolNot(p_isFastPath)));
    ca_.Branch(tmp24, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/regexp-match.tq", 66});
      CodeStubAssembler(state_).FailAssert("Torque assert '!isFastPath' failed", pos_stack);
    }
  }

  TNode<String> tmp25;
  TNode<String> tmp26;
  TNode<Smi> tmp27;
  TNode<Smi> tmp28;
  TNode<Smi> tmp29;
  TNode<BoolT> tmp30;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp25 = CodeStubAssembler(state_).StringConstant("u");
    tmp26 = CodeStubAssembler(state_).StringConstant("v");
    tmp27 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp28 = ca_.CallBuiltin<Smi>(Builtin::kStringIndexOf, TNode<Object>(), phi_bb9_4, tmp25, tmp27);
    tmp29 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp30 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp28}, TNode<Smi>{tmp29});
    ca_.Branch(tmp30, &block25, std::vector<compiler::Node*>{}, &block26, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp31;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp31 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block27, tmp31);
  }

  TNode<Smi> tmp32;
  TNode<Smi> tmp33;
  TNode<Smi> tmp34;
  TNode<BoolT> tmp35;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp32 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp33 = ca_.CallBuiltin<Smi>(Builtin::kStringIndexOf, TNode<Object>(), phi_bb9_4, tmp26, tmp32);
    tmp34 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp35 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp33}, TNode<Smi>{tmp34});
    ca_.Goto(&block27, tmp35);
  }

  TNode<BoolT> phi_bb27_8;
  TNode<Number> tmp36;
  TNode<FixedArray> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_8);
    tmp36 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    StoreLastIndex_0(state_, TNode<Context>{p_context}, TNode<JSAny>{p_regexp}, TNode<Number>{tmp36}, p_isFastPath);
    std::tie(tmp37, tmp38, tmp39) = NewGrowableFixedArray_0(state_).Flatten();
    ca_.Goto(&block30, tmp37, tmp38, tmp39);
  }

  TNode<FixedArray> phi_bb30_8;
  TNode<IntPtrT> phi_bb30_9;
  TNode<IntPtrT> phi_bb30_10;
  TNode<BoolT> tmp40;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_8, &phi_bb30_9, &phi_bb30_10);
    tmp40 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp40, &block28, std::vector<compiler::Node*>{phi_bb30_8, phi_bb30_9, phi_bb30_10}, &block29, std::vector<compiler::Node*>{phi_bb30_8, phi_bb30_9, phi_bb30_10});
  }

  TNode<FixedArray> phi_bb28_8;
  TNode<IntPtrT> phi_bb28_9;
  TNode<IntPtrT> phi_bb28_10;
  TNode<String> tmp41;
  TNode<JSAny> tmp42;
  TNode<Null> tmp43;
  TNode<BoolT> tmp44;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_8, &phi_bb28_9, &phi_bb28_10);
    tmp41 = CodeStubAssembler(state_).EmptyStringConstant();
    tmp42 = RegExpExec_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_regexp}, TNode<String>{p_string});
    tmp43 = Null_0(state_);
    tmp44 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp42}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp43});
    ca_.Branch(tmp44, &block35, std::vector<compiler::Node*>{phi_bb28_8, phi_bb28_9, phi_bb28_10}, &block36, std::vector<compiler::Node*>{phi_bb28_8, phi_bb28_9, phi_bb28_10});
  }

  TNode<FixedArray> phi_bb35_8;
  TNode<IntPtrT> phi_bb35_9;
  TNode<IntPtrT> phi_bb35_10;
  TNode<IntPtrT> tmp45;
  TNode<BoolT> tmp46;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_8, &phi_bb35_9, &phi_bb35_10);
    tmp45 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp46 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb35_10}, TNode<IntPtrT>{tmp45});
    ca_.Branch(tmp46, &block37, std::vector<compiler::Node*>{phi_bb35_8, phi_bb35_9, phi_bb35_10}, &block38, std::vector<compiler::Node*>{phi_bb35_8, phi_bb35_9, phi_bb35_10});
  }

  TNode<FixedArray> phi_bb36_8;
  TNode<IntPtrT> phi_bb36_9;
  TNode<IntPtrT> phi_bb36_10;
  TNode<Smi> tmp47;
  TNode<JSAny> tmp48;
  TNode<String> tmp49;
  TNode<BoolT> tmp50;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_8, &phi_bb36_9, &phi_bb36_10);
    tmp47 = SmiConstant_0(state_, IntegerLiteral(false, 0x0ull));
    tmp48 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<JSAny>{tmp42}, TNode<JSAny>{tmp47});
    tmp49 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp48});
    tmp50 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb36_10}, TNode<IntPtrT>{phi_bb36_9});
    ca_.Branch(tmp50, &block51, std::vector<compiler::Node*>{phi_bb36_8, phi_bb36_9, phi_bb36_10}, &block52, std::vector<compiler::Node*>{phi_bb36_8, phi_bb36_9, phi_bb36_10});
  }

  TNode<FixedArray> phi_bb37_8;
  TNode<IntPtrT> phi_bb37_9;
  TNode<IntPtrT> phi_bb37_10;
  TNode<Null> tmp51;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_8, &phi_bb37_9, &phi_bb37_10);
    tmp51 = Null_0(state_);
    ca_.Goto(&block39, phi_bb37_8, phi_bb37_9, phi_bb37_10, tmp51);
  }

  TNode<FixedArray> phi_bb38_8;
  TNode<IntPtrT> phi_bb38_9;
  TNode<IntPtrT> phi_bb38_10;
  TNode<NativeContext> tmp52;
  TNode<Map> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<BoolT> tmp55;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_8, &phi_bb38_9, &phi_bb38_10);
    tmp52 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp53 = CodeStubAssembler(state_).LoadJSArrayElementsMap(CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_ELEMENTS), TNode<NativeContext>{tmp52});
    tmp54 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp55 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb38_10}, TNode<IntPtrT>{tmp54});
    ca_.Branch(tmp55, &block43, std::vector<compiler::Node*>{phi_bb38_8, phi_bb38_9, phi_bb38_10, phi_bb38_10, phi_bb38_10}, &block44, std::vector<compiler::Node*>{phi_bb38_8, phi_bb38_9, phi_bb38_10, phi_bb38_10, phi_bb38_10});
  }

  TNode<FixedArray> phi_bb44_8;
  TNode<IntPtrT> phi_bb44_9;
  TNode<IntPtrT> phi_bb44_10;
  TNode<IntPtrT> phi_bb44_16;
  TNode<IntPtrT> phi_bb44_17;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_8, &phi_bb44_9, &phi_bb44_10, &phi_bb44_16, &phi_bb44_17);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb43_8;
  TNode<IntPtrT> phi_bb43_9;
  TNode<IntPtrT> phi_bb43_10;
  TNode<IntPtrT> phi_bb43_16;
  TNode<IntPtrT> phi_bb43_17;
  TNode<IntPtrT> tmp56;
  TNode<BoolT> tmp57;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_8, &phi_bb43_9, &phi_bb43_10, &phi_bb43_16, &phi_bb43_17);
    tmp56 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp57 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb43_17}, TNode<IntPtrT>{tmp56});
    ca_.Branch(tmp57, &block45, std::vector<compiler::Node*>{phi_bb43_8, phi_bb43_9, phi_bb43_10, phi_bb43_16, phi_bb43_17}, &block46, std::vector<compiler::Node*>{phi_bb43_8, phi_bb43_9, phi_bb43_10, phi_bb43_16, phi_bb43_17});
  }

  TNode<FixedArray> phi_bb46_8;
  TNode<IntPtrT> phi_bb46_9;
  TNode<IntPtrT> phi_bb46_10;
  TNode<IntPtrT> phi_bb46_16;
  TNode<IntPtrT> phi_bb46_17;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_8, &phi_bb46_9, &phi_bb46_10, &phi_bb46_16, &phi_bb46_17);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb45_8;
  TNode<IntPtrT> phi_bb45_9;
  TNode<IntPtrT> phi_bb45_10;
  TNode<IntPtrT> phi_bb45_16;
  TNode<IntPtrT> phi_bb45_17;
  TNode<BoolT> tmp58;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_8, &phi_bb45_9, &phi_bb45_10, &phi_bb45_16, &phi_bb45_17);
    tmp58 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb45_17}, TNode<IntPtrT>{phi_bb45_10});
    ca_.Branch(tmp58, &block47, std::vector<compiler::Node*>{phi_bb45_8, phi_bb45_9, phi_bb45_10, phi_bb45_16, phi_bb45_17}, &block48, std::vector<compiler::Node*>{phi_bb45_8, phi_bb45_9, phi_bb45_10, phi_bb45_16, phi_bb45_17});
  }

  TNode<FixedArray> phi_bb48_8;
  TNode<IntPtrT> phi_bb48_9;
  TNode<IntPtrT> phi_bb48_10;
  TNode<IntPtrT> phi_bb48_16;
  TNode<IntPtrT> phi_bb48_17;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_8, &phi_bb48_9, &phi_bb48_10, &phi_bb48_16, &phi_bb48_17);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb47_8;
  TNode<IntPtrT> phi_bb47_9;
  TNode<IntPtrT> phi_bb47_10;
  TNode<IntPtrT> phi_bb47_16;
  TNode<IntPtrT> phi_bb47_17;
  TNode<IntPtrT> tmp59;
  TNode<TheHole> tmp60;
  TNode<FixedArray> tmp61;
  TNode<Smi> tmp62;
  TNode<JSArray> tmp63;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_8, &phi_bb47_9, &phi_bb47_10, &phi_bb47_16, &phi_bb47_17);
    tmp59 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp60 = TheHole_0(state_);
    tmp61 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb47_8}, TNode<IntPtrT>{tmp59}, TNode<IntPtrT>{phi_bb47_10}, TNode<IntPtrT>{phi_bb47_17}, TNode<Hole>{tmp60});
    tmp62 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb47_10});
    tmp63 = CodeStubAssembler(state_).AllocateJSArray(TNode<Map>{tmp53}, TNode<FixedArrayBase>{tmp61}, TNode<Smi>{tmp62});
    ca_.Goto(&block39, phi_bb47_8, phi_bb47_9, phi_bb47_10, tmp63);
  }

  TNode<FixedArray> phi_bb39_8;
  TNode<IntPtrT> phi_bb39_9;
  TNode<IntPtrT> phi_bb39_10;
  TNode<Union<JSArray, Null>> phi_bb39_12;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_8, &phi_bb39_9, &phi_bb39_10, &phi_bb39_12);
    ca_.Goto(&block1, phi_bb39_12);
  }

  TNode<FixedArray> phi_bb52_8;
  TNode<IntPtrT> phi_bb52_9;
  TNode<IntPtrT> phi_bb52_10;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_8, &phi_bb52_9, &phi_bb52_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb51_8;
  TNode<IntPtrT> phi_bb51_9;
  TNode<IntPtrT> phi_bb51_10;
  TNode<BoolT> tmp64;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_8, &phi_bb51_9, &phi_bb51_10);
    tmp64 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb51_9}, TNode<IntPtrT>{phi_bb51_10});
    ca_.Branch(tmp64, &block53, std::vector<compiler::Node*>{phi_bb51_8, phi_bb51_9, phi_bb51_10}, &block54, std::vector<compiler::Node*>{phi_bb51_8, phi_bb51_9, phi_bb51_10});
  }

  TNode<FixedArray> phi_bb53_8;
  TNode<IntPtrT> phi_bb53_9;
  TNode<IntPtrT> phi_bb53_10;
  TNode<IntPtrT> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<BoolT> tmp71;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_8, &phi_bb53_9, &phi_bb53_10);
    tmp65 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp66 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb53_9}, TNode<IntPtrT>{tmp65});
    tmp67 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb53_9}, TNode<IntPtrT>{tmp66});
    tmp68 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp69 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp67}, TNode<IntPtrT>{tmp68});
    tmp70 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp71 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb53_10}, TNode<IntPtrT>{tmp70});
    ca_.Branch(tmp71, &block56, std::vector<compiler::Node*>{phi_bb53_8, phi_bb53_10}, &block57, std::vector<compiler::Node*>{phi_bb53_8, phi_bb53_10});
  }

  TNode<FixedArray> phi_bb57_8;
  TNode<IntPtrT> phi_bb57_10;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_8, &phi_bb57_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb56_8;
  TNode<IntPtrT> phi_bb56_10;
  TNode<IntPtrT> tmp72;
  TNode<BoolT> tmp73;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_8, &phi_bb56_10);
    tmp72 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp73 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp69}, TNode<IntPtrT>{tmp72});
    ca_.Branch(tmp73, &block58, std::vector<compiler::Node*>{phi_bb56_8, phi_bb56_10}, &block59, std::vector<compiler::Node*>{phi_bb56_8, phi_bb56_10});
  }

  TNode<FixedArray> phi_bb59_8;
  TNode<IntPtrT> phi_bb59_10;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_8, &phi_bb59_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb58_8;
  TNode<IntPtrT> phi_bb58_10;
  TNode<BoolT> tmp74;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_8, &phi_bb58_10);
    tmp74 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp69}, TNode<IntPtrT>{phi_bb58_10});
    ca_.Branch(tmp74, &block60, std::vector<compiler::Node*>{phi_bb58_8, phi_bb58_10}, &block61, std::vector<compiler::Node*>{phi_bb58_8, phi_bb58_10});
  }

  TNode<FixedArray> phi_bb61_8;
  TNode<IntPtrT> phi_bb61_10;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_8, &phi_bb61_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb60_8;
  TNode<IntPtrT> phi_bb60_10;
  TNode<IntPtrT> tmp75;
  TNode<TheHole> tmp76;
  TNode<FixedArray> tmp77;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_8, &phi_bb60_10);
    tmp75 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp76 = TheHole_0(state_);
    tmp77 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb60_8}, TNode<IntPtrT>{tmp75}, TNode<IntPtrT>{phi_bb60_10}, TNode<IntPtrT>{tmp69}, TNode<Hole>{tmp76});
    ca_.Goto(&block54, tmp77, tmp69, phi_bb60_10);
  }

  TNode<FixedArray> phi_bb54_8;
  TNode<IntPtrT> phi_bb54_9;
  TNode<IntPtrT> phi_bb54_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<IntPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<UintPtrT> tmp83;
  TNode<UintPtrT> tmp84;
  TNode<BoolT> tmp85;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_8, &phi_bb54_9, &phi_bb54_10);
    std::tie(tmp78, tmp79, tmp80) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb54_8}).Flatten();
    tmp81 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp82 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb54_10}, TNode<IntPtrT>{tmp81});
    tmp83 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb54_10});
    tmp84 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp80});
    tmp85 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp83}, TNode<UintPtrT>{tmp84});
    ca_.Branch(tmp85, &block66, std::vector<compiler::Node*>{phi_bb54_8, phi_bb54_9, phi_bb54_8, phi_bb54_10, phi_bb54_10, phi_bb54_10, phi_bb54_10}, &block67, std::vector<compiler::Node*>{phi_bb54_8, phi_bb54_9, phi_bb54_8, phi_bb54_10, phi_bb54_10, phi_bb54_10, phi_bb54_10});
  }

  TNode<FixedArray> phi_bb66_8;
  TNode<IntPtrT> phi_bb66_9;
  TNode<FixedArray> phi_bb66_14;
  TNode<IntPtrT> phi_bb66_18;
  TNode<IntPtrT> phi_bb66_19;
  TNode<IntPtrT> phi_bb66_23;
  TNode<IntPtrT> phi_bb66_24;
  TNode<IntPtrT> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<Union<HeapObject, TaggedIndex>> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Smi> tmp90;
  TNode<Smi> tmp91;
  TNode<BoolT> tmp92;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_8, &phi_bb66_9, &phi_bb66_14, &phi_bb66_18, &phi_bb66_19, &phi_bb66_23, &phi_bb66_24);
    tmp86 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb66_24});
    tmp87 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp79}, TNode<IntPtrT>{tmp86});
    std::tie(tmp88, tmp89) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp78}, TNode<IntPtrT>{tmp87}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp88, tmp89}, tmp49);
    tmp90 = CodeStubAssembler(state_).LoadStringLengthAsSmi(TNode<String>{tmp49});
    tmp91 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp92 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp90}, TNode<Smi>{tmp91});
    ca_.Branch(tmp92, &block70, std::vector<compiler::Node*>{phi_bb66_8, phi_bb66_9}, &block71, std::vector<compiler::Node*>{phi_bb66_8, phi_bb66_9});
  }

  TNode<FixedArray> phi_bb67_8;
  TNode<IntPtrT> phi_bb67_9;
  TNode<FixedArray> phi_bb67_14;
  TNode<IntPtrT> phi_bb67_18;
  TNode<IntPtrT> phi_bb67_19;
  TNode<IntPtrT> phi_bb67_23;
  TNode<IntPtrT> phi_bb67_24;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_8, &phi_bb67_9, &phi_bb67_14, &phi_bb67_18, &phi_bb67_19, &phi_bb67_23, &phi_bb67_24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb70_8;
  TNode<IntPtrT> phi_bb70_9;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_8, &phi_bb70_9);
    ca_.Goto(&block30, phi_bb70_8, phi_bb70_9, tmp82);
  }

  TNode<FixedArray> phi_bb71_8;
  TNode<IntPtrT> phi_bb71_9;
  TNode<JSAny> tmp93;
  TNode<Number> tmp94;
  TNode<Number> tmp95;
  TNode<Number> tmp96;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_8, &phi_bb71_9);
    tmp93 = LoadLastIndex_0(state_, TNode<Context>{p_context}, TNode<JSAny>{p_regexp}, p_isFastPath);
    tmp94 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp93});
    tmp95 = UnsafeCast_Number_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp94});
    tmp96 = RegExpBuiltinsAssembler(state_).AdvanceStringIndex(TNode<String>{p_string}, TNode<Number>{tmp95}, TNode<BoolT>{phi_bb27_8}, p_isFastPath);
    StoreLastIndex_0(state_, TNode<Context>{p_context}, TNode<JSAny>{p_regexp}, TNode<Number>{tmp96}, p_isFastPath);
    ca_.Goto(&block30, phi_bb71_8, phi_bb71_9, tmp82);
  }

  TNode<FixedArray> phi_bb29_8;
  TNode<IntPtrT> phi_bb29_9;
  TNode<IntPtrT> phi_bb29_10;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_8, &phi_bb29_9, &phi_bb29_10);
    VerifiedUnreachable_0(state_);
  }

  TNode<JSAny> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block72, phi_bb1_3);
  }

  TNode<JSAny> phi_bb72_3;
    ca_.Bind(&block72, &phi_bb72_3);
  return TNode<JSAny>{phi_bb72_3};
}

// https://crsrc.org/c/v8/src/builtins/regexp-match.tq?l=116&c=1
TNode<JSAny> FastRegExpPrototypeMatchBody_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSRegExp> p_receiver, TNode<String> p_string) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RegExpPrototypeMatchBody_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver}, TNode<String>{p_string}, true);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSAny>{tmp0};
}

// https://crsrc.org/c/v8/src/builtins/regexp-match.tq?l=121&c=1
TNode<JSAny> SlowRegExpPrototypeMatchBody_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<String> p_string) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RegExpPrototypeMatchBody_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver}, TNode<String>{p_string}, false);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSAny>{tmp0};
}

TF_BUILTIN(RegExpMatchFast, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSRegExp> parameter1 = UncheckedParameter<JSRegExp>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<String> parameter2 = UncheckedParameter<String>(Descriptor::kString);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FastRegExpPrototypeMatchBody_0(state_, TNode<Context>{parameter0}, TNode<JSRegExp>{parameter1}, TNode<String>{parameter2});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(RegExpPrototypeMatch, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kString);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<String> tmp1;
  TNode<JSRegExp> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).ThrowIfNotJSReceiver(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kIncompatibleMethodReceiver), "RegExp.prototype.@@match");
    tmp0 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter2});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSRegExp_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block3);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block4);
    }
  }

  TNode<JSAny> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = SlowRegExpPrototypeMatchBody_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}, TNode<String>{tmp1});
    CodeStubAssembler(state_).Return(tmp4);
  }

  TNode<JSAny> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = ca_.CallBuiltin<JSAny>(Builtin::kRegExpMatchFast, parameter0, tmp2, tmp1);
    CodeStubAssembler(state_).Return(tmp5);
  }
}

// https://crsrc.org/c/v8/src/builtins/regexp-match.tq?l=28&c=12
TNode<BoolT> Is_FastJSRegExp_JSReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSRegExp> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSRegExp_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_o}, &label1);
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
