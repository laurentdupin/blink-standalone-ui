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
#include "torque-generated/src/builtins/string-repeat-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/string-repeat-tq-csa.h"
#include "torque-generated/src/objects/heap-number-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/string-repeat.tq?l=6&c=1
const char* kBuiltinName_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return "String.prototype.repeat";}

TF_BUILTIN(StringRepeat, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<String> parameter1 = UncheckedParameter<String>(Descriptor::kString);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kCount);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, String, IntPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, String, IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, String, IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, String, IntPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, String, IntPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-repeat.tq", 10});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count >= 0' failed", pos_stack);
    }
  }

  TNode<String> tmp2;
  TNode<BoolT> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = kEmptyString_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{parameter1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-repeat.tq", 11});
      CodeStubAssembler(state_).FailAssert("Torque assert 'string != kEmptyString' failed", pos_stack);
    }
  }

  TNode<String> tmp4;
  TNode<IntPtrT> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = kEmptyString_0(state_);
    tmp5 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    ca_.Goto(&block7, tmp4, parameter1, tmp5);
  }

  TNode<String> phi_bb7_3;
  TNode<String> phi_bb7_4;
  TNode<IntPtrT> phi_bb7_5;
  TNode<BoolT> tmp6;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_3, &phi_bb7_4, &phi_bb7_5);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp6, &block5, std::vector<compiler::Node*>{phi_bb7_3, phi_bb7_4, phi_bb7_5}, &block6, std::vector<compiler::Node*>{phi_bb7_3, phi_bb7_4, phi_bb7_5});
  }

  TNode<String> phi_bb5_3;
  TNode<String> phi_bb5_4;
  TNode<IntPtrT> phi_bb5_5;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_3, &phi_bb5_4, &phi_bb5_5);
    tmp7 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp8 = CodeStubAssembler(state_).WordAnd(TNode<IntPtrT>{phi_bb5_5}, TNode<IntPtrT>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp10 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp9});
    ca_.Branch(tmp10, &block8, std::vector<compiler::Node*>{phi_bb5_3, phi_bb5_4, phi_bb5_5}, &block9, std::vector<compiler::Node*>{phi_bb5_3, phi_bb5_4, phi_bb5_5});
  }

  TNode<String> phi_bb8_3;
  TNode<String> phi_bb8_4;
  TNode<IntPtrT> phi_bb8_5;
  TNode<String> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_3, &phi_bb8_4, &phi_bb8_5);
    tmp11 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{phi_bb8_3}, TNode<String>{phi_bb8_4});
    ca_.Goto(&block9, tmp11, phi_bb8_4, phi_bb8_5);
  }

  TNode<String> phi_bb9_3;
  TNode<String> phi_bb9_4;
  TNode<IntPtrT> phi_bb9_5;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3, &phi_bb9_4, &phi_bb9_5);
    tmp12 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp13 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb9_5}, TNode<IntPtrT>{tmp12});
    tmp14 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp14});
    ca_.Branch(tmp15, &block10, std::vector<compiler::Node*>{phi_bb9_4}, &block11, std::vector<compiler::Node*>{phi_bb9_4});
  }

  TNode<String> phi_bb10_4;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_4);
    ca_.Goto(&block6, phi_bb9_3, phi_bb10_4, tmp13);
  }

  TNode<String> phi_bb11_4;
  TNode<String> tmp16;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_4);
    tmp16 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{phi_bb11_4}, TNode<String>{phi_bb11_4});
    ca_.Goto(&block7, phi_bb9_3, tmp16, tmp13);
  }

  TNode<String> phi_bb6_3;
  TNode<String> phi_bb6_4;
  TNode<IntPtrT> phi_bb6_5;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_3, &phi_bb6_4, &phi_bb6_5);
    CodeStubAssembler(state_).Return(phi_bb6_3);
  }
}

TF_BUILTIN(StringPrototypeRepeat, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kCount);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  TNode<String> tmp1;
  TNode<Number> tmp2;
  TNode<Smi> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_String_constexpr_string_0(state_, kBuiltinName_0(state_));
    tmp1 = CodeStubAssembler(state_).ToThisString(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TNode<String>{tmp0});
    tmp2 = ToInteger_Inline_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter2});
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_Smi_0(state_, TNode<Object>{tmp2}, &label4);
    ca_.Goto(&block9);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block10);
    }
  }

  TNode<BoolT> tmp5;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp5 = CodeStubAssembler(state_).IsNumberNormalized(TNode<Number>{ca_.UncheckedCast<HeapNumber>(tmp2)});
    ca_.Branch(tmp5, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp6;
  TNode<BoolT> tmp7;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp6 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp3}, TNode<Smi>{tmp6});
    ca_.Branch(tmp7, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block4);
  }

  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp8 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp9 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp3}, TNode<Smi>{tmp8});
    ca_.Branch(tmp9, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp10;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp10 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block17, tmp10);
  }

  TNode<Uint32T> tmp11;
  TNode<Uint32T> tmp12;
  TNode<BoolT> tmp13;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp11 = CodeStubAssembler(state_).LoadStringLengthAsWord32(TNode<String>{tmp1});
    tmp12 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp13 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp11}, TNode<Uint32T>{tmp12});
    ca_.Goto(&block17, tmp13);
  }

  TNode<BoolT> phi_bb17_7;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7);
    ca_.Branch(phi_bb17_7, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block6);
  }

  TNode<Smi> tmp14;
  TNode<BoolT> tmp15;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp14 = FromConstexpr_Smi_constexpr_int31_0(state_, String::kMaxLength);
    tmp15 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp3}, TNode<Smi>{tmp14});
    ca_.Branch(tmp15, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block2);
  }

  TNode<String> tmp16;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp16 = ca_.CallBuiltin<String>(Builtin::kStringRepeat, parameter0, tmp1, tmp3);
    CodeStubAssembler(state_).Return(tmp16);
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/string-repeat.tq", 54});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsNumberNormalized(heapNum)' failed", pos_stack);
    }
  }

  TNode<Float64T> tmp17;
  TNode<Float64T> tmp18;
  TNode<BoolT> tmp19;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp17 = LoadHeapNumberValue_0(state_, TNode<HeapNumber>{ca_.UncheckedCast<HeapNumber>(tmp2)});
    tmp18 = FromConstexpr_float64_constexpr_float64_0(state_, V8_INFINITY);
    tmp19 = CodeStubAssembler(state_).Float64Equal(TNode<Float64T>{tmp17}, TNode<Float64T>{tmp18});
    ca_.Branch(tmp19, &block24, std::vector<compiler::Node*>{}, &block25, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp20;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block26, tmp20);
  }

  TNode<Float64T> tmp21;
  TNode<BoolT> tmp22;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp21 = FromConstexpr_float64_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp22 = CodeStubAssembler(state_).Float64LessThan(TNode<Float64T>{tmp17}, TNode<Float64T>{tmp21});
    ca_.Goto(&block26, tmp22);
  }

  TNode<BoolT> phi_bb26_8;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_8);
    ca_.Branch(phi_bb26_8, &block22, std::vector<compiler::Node*>{}, &block23, std::vector<compiler::Node*>{});
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block4);
  }

  TNode<Uint32T> tmp23;
  TNode<Uint32T> tmp24;
  TNode<BoolT> tmp25;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp23 = CodeStubAssembler(state_).LoadStringLengthAsWord32(TNode<String>{tmp1});
    tmp24 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp25 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp23}, TNode<Uint32T>{tmp24});
    ca_.Branch(tmp25, &block27, std::vector<compiler::Node*>{}, &block28, std::vector<compiler::Node*>{});
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block6);
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    ca_.Goto(&block2);
  }

  TNode<String> tmp26;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp26 = kEmptyString_0(state_);
    CodeStubAssembler(state_).Return(tmp26);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidCountValue), TNode<Object>{parameter2});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, parameter0);
    CodeStubAssembler(state_).Unreachable();
  }
}

} // namespace internal
} // namespace v8
