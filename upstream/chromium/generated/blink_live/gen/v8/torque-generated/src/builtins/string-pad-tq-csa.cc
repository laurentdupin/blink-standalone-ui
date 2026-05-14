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
#include "torque-generated/src/builtins/string-pad-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/string-pad-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/string-pad.tq?l=12&c=1
int31_t kStringPadStart_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull)));}

// https://crsrc.org/c/v8/src/builtins/string-pad.tq?l=13&c=1
int31_t kStringPadEnd_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull)));}

// https://crsrc.org/c/v8/src/builtins/string-pad.tq?l=15&c=1
TNode<String> StringPad_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_receiver, TorqueStructArguments p_arguments, const char* p_methodName, int31_t p_variant) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block25(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block36(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  TNode<String> tmp1;
  TNode<Smi> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_String_constexpr_string_0(state_, p_methodName);
    tmp1 = CodeStubAssembler(state_).ToThisString(TNode<Context>{p_context}, TNode<JSAny>{p_receiver}, TNode<String>{tmp0});
    tmp2 = CodeStubAssembler(state_).LoadStringLengthAsSmi(TNode<String>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block1, tmp1);
  }

  TNode<IntPtrT> tmp5;
  TNode<JSAny> tmp6;
  TNode<Number> tmp7;
  TNode<BoolT> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{p_arguments.frame}, TNode<RawPtrT>{p_arguments.base}, TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{p_arguments.actual_count}}, TNode<IntPtrT>{tmp5});
    tmp7 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp6});
    tmp8 = CodeStubAssembler(state_).IsNumberNormalized(TNode<Number>{tmp7});
    ca_.Branch(tmp8, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-pad.tq", 25});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsNumberNormalized(maxLength)' failed", pos_stack);
    }
  }

  TNode<Smi> tmp9;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = Cast_Smi_0(state_, TNode<Object>{tmp7}, &label10);
    ca_.Goto(&block8);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block6);
  }

  TNode<BoolT> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp11 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp9}, TNode<Smi>{tmp2});
    ca_.Branch(tmp11, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block1, tmp1);
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block6);
  }

  TNode<String> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp12 = FromConstexpr_String_constexpr_string_0(state_, " ");
    tmp13 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp14 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp15 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{tmp14});
    ca_.Branch(tmp15, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{tmp12, tmp13});
  }

  TNode<IntPtrT> tmp16;
  TNode<JSAny> tmp17;
  TNode<Undefined> tmp18;
  TNode<BoolT> tmp19;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp16 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp17 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{p_arguments.frame}, TNode<RawPtrT>{p_arguments.base}, TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{p_arguments.actual_count}}, TNode<IntPtrT>{tmp16});
    tmp18 = Undefined_0(state_);
    tmp19 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp17}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp18});
    ca_.Branch(tmp19, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{tmp12, tmp13});
  }

  TNode<String> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<BoolT> tmp23;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp20 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<JSAny>{tmp17});
    tmp21 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{tmp20});
    tmp22 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp23 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp22});
    ca_.Branch(tmp23, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block1, tmp1);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block15, tmp20, tmp21);
  }

  TNode<String> phi_bb15_9;
  TNode<IntPtrT> phi_bb15_10;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_9, &phi_bb15_10);
    ca_.Goto(&block13, phi_bb15_9, phi_bb15_10);
  }

  TNode<String> phi_bb13_9;
  TNode<IntPtrT> phi_bb13_10;
  TNode<IntPtrT> tmp24;
  TNode<BoolT> tmp25;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_9, &phi_bb13_10);
    tmp24 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp25 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb13_10}, TNode<IntPtrT>{tmp24});
    ca_.Branch(tmp25, &block18, std::vector<compiler::Node*>{phi_bb13_9, phi_bb13_10}, &block19, std::vector<compiler::Node*>{phi_bb13_9, phi_bb13_10});
  }

  TNode<String> phi_bb19_9;
  TNode<IntPtrT> phi_bb19_10;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_9, &phi_bb19_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-pad.tq", 52});
      CodeStubAssembler(state_).FailAssert("Torque assert 'fillLength > 0' failed", pos_stack);
    }
  }

  TNode<String> phi_bb18_9;
  TNode<IntPtrT> phi_bb18_10;
  TNode<BoolT> tmp26;
  TNode<BoolT> tmp27;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_9, &phi_bb18_10);
    tmp26 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{tmp7});
    tmp27 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp26});
    ca_.Branch(tmp27, &block20, std::vector<compiler::Node*>{phi_bb18_9, phi_bb18_10}, &block21, std::vector<compiler::Node*>{phi_bb18_9, phi_bb18_10});
  }

  TNode<String> phi_bb20_9;
  TNode<IntPtrT> phi_bb20_10;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_9, &phi_bb20_10);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb21_9;
  TNode<IntPtrT> phi_bb21_10;
  TNode<Smi> tmp28;
  TNode<Smi> tmp29;
  TNode<BoolT> tmp30;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_9, &phi_bb21_10);
    tmp28 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp7});
    tmp29 = CodeStubAssembler(state_).SmiConstant(String::kMaxLength);
    tmp30 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp28}, TNode<Smi>{tmp29});
    ca_.Branch(tmp30, &block22, std::vector<compiler::Node*>{phi_bb21_9, phi_bb21_10}, &block23, std::vector<compiler::Node*>{phi_bb21_9, phi_bb21_10});
  }

  TNode<String> phi_bb22_9;
  TNode<IntPtrT> phi_bb22_10;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_9, &phi_bb22_10);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb23_9;
  TNode<IntPtrT> phi_bb23_10;
  TNode<BoolT> tmp31;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_9, &phi_bb23_10);
    tmp31 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp28}, TNode<Smi>{tmp2});
    ca_.Branch(tmp31, &block24, std::vector<compiler::Node*>{phi_bb23_9, phi_bb23_10}, &block25, std::vector<compiler::Node*>{phi_bb23_9, phi_bb23_10});
  }

  TNode<String> phi_bb25_9;
  TNode<IntPtrT> phi_bb25_10;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_9, &phi_bb25_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-pad.tq", 62});
      CodeStubAssembler(state_).FailAssert("Torque assert 'smiMaxLength > stringLength' failed", pos_stack);
    }
  }

  TNode<String> phi_bb24_9;
  TNode<IntPtrT> phi_bb24_10;
  TNode<Smi> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_9, &phi_bb24_10);
    tmp32 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp28}, TNode<Smi>{tmp2});
    tmp33 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp34 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb24_10}, TNode<IntPtrT>{tmp33});
    ca_.Branch(tmp34, &block26, std::vector<compiler::Node*>{phi_bb24_9, phi_bb24_10}, &block27, std::vector<compiler::Node*>{phi_bb24_9, phi_bb24_10});
  }

  TNode<String> phi_bb26_9;
  TNode<IntPtrT> phi_bb26_10;
  TNode<String> tmp35;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_9, &phi_bb26_10);
    tmp35 = ca_.CallBuiltin<String>(Builtin::kStringRepeat, p_context, phi_bb26_9, tmp32);
    ca_.Goto(&block28, phi_bb26_9, phi_bb26_10, tmp35);
  }

  TNode<String> phi_bb27_9;
  TNode<IntPtrT> phi_bb27_10;
  TNode<Int32T> tmp36;
  TNode<Int32T> tmp37;
  TNode<Int32T> tmp38;
  TNode<Int32T> tmp39;
  TNode<Smi> tmp40;
  TNode<String> tmp41;
  TNode<Int32T> tmp42;
  TNode<BoolT> tmp43;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_9, &phi_bb27_10);
    tmp36 = CodeStubAssembler(state_).TruncateIntPtrToInt32(TNode<IntPtrT>{phi_bb27_10});
    tmp37 = Convert_int32_Smi_0(state_, TNode<Smi>{tmp32});
    tmp38 = CodeStubAssembler(state_).Int32Div(TNode<Int32T>{tmp37}, TNode<Int32T>{tmp36});
    tmp39 = CodeStubAssembler(state_).Int32Mod(TNode<Int32T>{tmp37}, TNode<Int32T>{tmp36});
    tmp40 = Convert_Smi_int32_0(state_, TNode<Int32T>{tmp38});
    tmp41 = ca_.CallBuiltin<String>(Builtin::kStringRepeat, p_context, phi_bb27_9, tmp40);
    tmp42 = FromConstexpr_int32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp43 = CodeStubAssembler(state_).Word32NotEqual(TNode<Int32T>{tmp39}, TNode<Int32T>{tmp42});
    ca_.Branch(tmp43, &block29, std::vector<compiler::Node*>{phi_bb27_9, phi_bb27_10}, &block30, std::vector<compiler::Node*>{phi_bb27_9, phi_bb27_10, tmp41});
  }

  TNode<String> phi_bb29_9;
  TNode<IntPtrT> phi_bb29_10;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<String> tmp46;
  TNode<String> tmp47;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_9, &phi_bb29_10);
    tmp44 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp39});
    tmp45 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp46 = ca_.CallBuiltin<String>(Builtin::kStringSubstring, p_context, phi_bb29_9, tmp45, tmp44);
    tmp47 = StringAdd_0(state_, TNode<Context>{p_context}, TNode<String>{tmp41}, TNode<String>{tmp46});
    ca_.Goto(&block30, phi_bb29_9, phi_bb29_10, tmp47);
  }

  TNode<String> phi_bb30_9;
  TNode<IntPtrT> phi_bb30_10;
  TNode<String> phi_bb30_13;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_9, &phi_bb30_10, &phi_bb30_13);
    ca_.Goto(&block28, phi_bb30_9, phi_bb30_10, phi_bb30_13);
  }

  TNode<String> phi_bb28_9;
  TNode<IntPtrT> phi_bb28_10;
  TNode<String> phi_bb28_13;
  TNode<Smi> tmp48;
  TNode<BoolT> tmp49;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_9, &phi_bb28_10, &phi_bb28_13);
    tmp48 = CodeStubAssembler(state_).LoadStringLengthAsSmi(TNode<String>{phi_bb28_13});
    tmp49 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp32}, TNode<Smi>{tmp48});
    ca_.Branch(tmp49, &block31, std::vector<compiler::Node*>{phi_bb28_9, phi_bb28_10, phi_bb28_13}, &block32, std::vector<compiler::Node*>{phi_bb28_9, phi_bb28_10, phi_bb28_13});
  }

  TNode<String> phi_bb32_9;
  TNode<IntPtrT> phi_bb32_10;
  TNode<String> phi_bb32_13;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_9, &phi_bb32_10, &phi_bb32_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-pad.tq", 88});
      CodeStubAssembler(state_).FailAssert("Torque assert 'padLength == padding.length_smi' failed", pos_stack);
    }
  }

  TNode<String> phi_bb31_9;
  TNode<IntPtrT> phi_bb31_10;
  TNode<String> phi_bb31_13;
  TNode<BoolT> tmp50;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_9, &phi_bb31_10, &phi_bb31_13);
    tmp50 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt31Equal(p_variant, kStringPadStart_0(state_))));
    ca_.Branch(tmp50, &block33, std::vector<compiler::Node*>{phi_bb31_9, phi_bb31_10, phi_bb31_13}, &block34, std::vector<compiler::Node*>{phi_bb31_9, phi_bb31_10, phi_bb31_13});
  }

  TNode<String> phi_bb33_9;
  TNode<IntPtrT> phi_bb33_10;
  TNode<String> phi_bb33_13;
  TNode<String> tmp51;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_9, &phi_bb33_10, &phi_bb33_13);
    tmp51 = StringAdd_0(state_, TNode<Context>{p_context}, TNode<String>{phi_bb33_13}, TNode<String>{tmp1});
    ca_.Goto(&block1, tmp51);
  }

  TNode<String> phi_bb34_9;
  TNode<IntPtrT> phi_bb34_10;
  TNode<String> phi_bb34_13;
  TNode<BoolT> tmp52;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_9, &phi_bb34_10, &phi_bb34_13);
    tmp52 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt31Equal(p_variant, kStringPadEnd_0(state_))));
    ca_.Branch(tmp52, &block35, std::vector<compiler::Node*>{phi_bb34_9, phi_bb34_10, phi_bb34_13}, &block36, std::vector<compiler::Node*>{phi_bb34_9, phi_bb34_10, phi_bb34_13});
  }

  TNode<String> phi_bb36_9;
  TNode<IntPtrT> phi_bb36_10;
  TNode<String> phi_bb36_13;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_9, &phi_bb36_10, &phi_bb36_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-pad.tq", 92});
      CodeStubAssembler(state_).FailAssert("Torque assert 'variant == kStringPadEnd' failed", pos_stack);
    }
  }

  TNode<String> phi_bb35_9;
  TNode<IntPtrT> phi_bb35_10;
  TNode<String> phi_bb35_13;
  TNode<String> tmp53;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_9, &phi_bb35_10, &phi_bb35_13);
    tmp53 = StringAdd_0(state_, TNode<Context>{p_context}, TNode<String>{tmp1}, TNode<String>{phi_bb35_13});
    ca_.Goto(&block1, tmp53);
  }

  TNode<String> phi_bb1_6;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_6);
    ca_.Goto(&block37, phi_bb1_6);
  }

  TNode<String> phi_bb37_6;
    ca_.Bind(&block37, &phi_bb37_6);
  return TNode<String>{phi_bb37_6};
}

TF_BUILTIN(StringPrototypePadStart, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  TNode<String> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = StringPad_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, "String.prototype.padStart", kStringPadStart_0(state_));
    arguments.PopAndReturn(tmp0);
  }
}

TF_BUILTIN(StringPrototypePadEnd, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  TNode<String> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = StringPad_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, "String.prototype.padEnd", kStringPadEnd_0(state_));
    arguments.PopAndReturn(tmp0);
  }
}

} // namespace internal
} // namespace v8
