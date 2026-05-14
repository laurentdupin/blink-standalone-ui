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
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-slice-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/descriptor-array-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/array.tq?l=19&c=1
void EnsureWriteableFastElements_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_array) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<Int32T> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_array, tmp0});
    tmp2 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp1});
    tmp3 = CodeStubAssembler(state_).IsFastElementsKind(TNode<Int32T>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsFastElementsKind(array.map.elements_kind)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp4;
  TNode<FixedArrayBase> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Map> tmp7;
  TNode<Map> tmp8;
  TNode<BoolT> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp5 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_array, tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp5, tmp6});
    tmp8 = kCOWMap_0(state_);
    tmp9 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp7}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp8});
    ca_.Branch(tmp9, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp10;
  TNode<Map> tmp11;
  TNode<Int32T> tmp12;
  TNode<BoolT> tmp13;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp11 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_array, tmp10});
    tmp12 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp11});
    tmp13 = CodeStubAssembler(state_).IsFastSmiOrTaggedElementsKind(TNode<Int32T>{tmp12});
    ca_.Branch(tmp13, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array.tq", 28});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsFastSmiOrTaggedElementsKind(array.map.elements_kind)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp14;
  TNode<Number> tmp15;
  TNode<Smi> tmp16;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp15 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_array, tmp14});
    compiler::CodeAssemblerLabel label17(&ca_);
    tmp16 = Cast_Smi_0(state_, TNode<Object>{tmp15}, &label17);
    ca_.Goto(&block10);
    if (label17.is_used()) {
      ca_.Bind(&label17);
      ca_.Goto(&block11);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array.tq:30:68");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<FixedArray> tmp20;
  TNode<TheHole> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<FixedArray> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<FixedArrayBase> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<Map> tmp27;
  TNode<Map> tmp28;
  TNode<BoolT> tmp29;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp18 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp16});
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp20 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp5});
    tmp21 = TheHole_0(state_);
    tmp22 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp23 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp20}, TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp18}, TNode<Hole>{tmp21});
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{p_array, tmp19}, tmp23);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp25 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_array, tmp24});
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp27 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp25, tmp26});
    tmp28 = kCOWMap_0(state_);
    tmp29 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp27}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp28});
    ca_.Branch(tmp29, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array.tq", 33});
      CodeStubAssembler(state_).FailAssert("Torque assert 'array.elements.map != kCOWMap' failed", pos_stack);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block14);
  }

    ca_.Bind(&block14);
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=36&c=1
TNode<JSAny> LoadElementOrUndefined_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_a, TNode<Smi> p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_a}).Flatten();
    tmp3 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_i});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Object> tmp11;
  TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> tmp12;
  TNode<JSAny> tmp13;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp3});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp8}).Flatten();
    tmp11 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp9, tmp10});
    tmp12 = UnsafeCast_Smi_OR_JSReceiver_OR_Undefined_OR_Null_OR_Boolean_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_TheHole_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp11});
    tmp13 = ReplaceTheHoleWithUndefined_0(state_, TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>>{tmp12});
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
  return TNode<JSAny>{tmp13};
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=42&c=1
TNode<Union<HeapNumber, Smi, Undefined>> LoadElementOrUndefined_1(compiler::CodeAssemblerState* state_, TNode<FixedDoubleArray> p_a, TNode<Smi> p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Union<HeapNumber, Smi, Undefined>> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Union<HeapNumber, Smi, Undefined>> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{p_a}).Flatten();
    tmp3 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_i});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<BoolT> tmp11;
  TNode<BoolT> tmp12;
  TNode<Float64T> tmp13;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp7 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp3});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp8}).Flatten();
    std::tie(tmp11, tmp12, tmp13) = LoadFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp9}, TNode<IntPtrT>{tmp10}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp11, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Undefined> tmp14;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp14 = Undefined_0(state_);
    ca_.Goto(&block1, tmp14);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Branch(tmp12, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp15;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp15 = Undefined_0(state_);
    ca_.Goto(&block1, tmp15);
  }

  TNode<HeapNumber> tmp16;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp16 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp13});
    ca_.Goto(&block1, tmp16);
  }

  TNode<Union<HeapNumber, Smi, Undefined>> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block19, phi_bb1_2);
  }

  TNode<Union<HeapNumber, Smi, Undefined>> phi_bb19_2;
    ca_.Bind(&block19, &phi_bb19_2);
  return TNode<Union<HeapNumber, Smi, Undefined>>{phi_bb19_2};
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=49&c=1
void StoreArrayHole_0(compiler::CodeAssemblerState* state_, TNode<FixedDoubleArray> p_elements, TNode<Smi> p_k) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{p_elements}).Flatten();
    tmp3 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_k});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<BoolT> tmp11;
  TNode<BoolT> tmp12;
  TNode<Float64T> tmp13;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp3});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp8}).Flatten();
    std::tie(tmp11, tmp12, tmp13) = kDoubleHole_0(state_).Flatten();
    StoreFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp9}, TNode<IntPtrT>{tmp10}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_undefined_or_hole_0{TNode<BoolT>{tmp11}, TNode<BoolT>{tmp12}, TNode<Float64T>{tmp13}});
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=53&c=1
void StoreArrayHole_1(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_elements, TNode<Smi> p_k) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_elements}).Flatten();
    tmp3 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_k});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<TheHole> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp3});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp8}).Flatten();
    tmp11 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp9, tmp10}, tmp11);
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=65&c=1
void EnsureArrayLengthWritable_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Map> p_map, compiler::CodeAssemblerLabel* label_Bailout) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ConstructorBuiltinsAssembler(state_).IsDictionaryMap(TNode<Map>{p_map});
    ca_.Branch(tmp0, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp1;
  TNode<Union<DescriptorArray, WasmStruct>> tmp2;
  TNode<DescriptorArray> tmp3;
  TNode<Union<HeapObject, TaggedIndex>> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp2 = CodeStubAssembler(state_).LoadReference<Union<DescriptorArray, WasmStruct>>(CodeStubAssembler::Reference{p_map, tmp1});
    tmp3 = UnsafeCast_DescriptorArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp2});
    std::tie(tmp4, tmp5, tmp6) = FieldSliceDescriptorArrayDescriptors_0(state_, TNode<DescriptorArray>{tmp3}).Flatten();
    tmp7 = Convert_intptr_constexpr_int31_0(state_, JSArray::kLengthDescriptorIndex);
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp10 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp10, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Union<HeapObject, TaggedIndex>> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Union<Name, Undefined>> tmp15;
  TNode<String> tmp16;
  TNode<BoolT> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp11 = TimesSizeOf_DescriptorEntry_0(state_, TNode<IntPtrT>{tmp7});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_DescriptorEntry_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp4}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<Union<Name, Undefined>>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = CodeStubAssembler(state_).LengthStringConstant();
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{tmp15}, TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{tmp16});
    ca_.Branch(tmp17, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:126:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array.tq", 80});
      CodeStubAssembler(state_).FailAssert("Torque assert 'TaggedEqual(descriptor->key, LengthStringConstant())' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Union<Smi, Undefined>> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<BoolT> tmp25;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp18 = FromConstexpr_intptr_constexpr_intptr_0(state_, 4);
    tmp19 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp18});
    tmp20 = CodeStubAssembler(state_).LoadReference<Union<Smi, Undefined>>(CodeStubAssembler::Reference{tmp13, tmp19});
    tmp21 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp20});
    tmp22 = FromConstexpr_Smi_constexpr_int31_0(state_, PropertyDetails::kAttributesReadOnlyMask);
    tmp23 = CodeStubAssembler(state_).SmiAnd(TNode<Smi>{tmp21}, TNode<Smi>{tmp22});
    tmp24 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp25 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp23}, TNode<Smi>{tmp24});
    ca_.Branch(tmp25, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Goto(&block1);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block17);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Bailout);
  }

    ca_.Bind(&block17);
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=87&c=1
TNode<JSArray> CreateJSArrayWithElements_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_array) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<NativeContext> tmp0;
  TNode<Map> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Uint32T> tmp3;
  TNode<Smi> tmp4;
  TNode<JSArray> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp1 = CodeStubAssembler(state_).LoadJSArrayElementsMap(CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_ELEMENTS), TNode<NativeContext>{tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{p_array, tmp2});
    tmp4 = Convert_Smi_uint32_0(state_, TNode<Uint32T>{tmp3});
    tmp5 = CodeStubAssembler(state_).AllocateJSArray(TNode<Map>{tmp1}, TNode<FixedArrayBase>{p_array}, TNode<Smi>{tmp4});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSArray>{tmp5};
}

TF_BUILTIN(ArraySortNoopEagerDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kComparefn);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter1}, TNode<JSAny>{parameter3});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(ArraySortNoopLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kComparefn);
  USE(parameter3);
  TNode<JSAny> parameter4 = UncheckedParameter<JSAny>(Descriptor::kResult);
  USE(parameter4);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter1}, TNode<JSAny>{parameter3});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

// https://crsrc.org/c/v8/src/builtins/array.tq?l=77&c=7
TNode<DescriptorArray> UnsafeCast_DescriptorArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_DescriptorArray_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<DescriptorArray> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<DescriptorArray>{tmp1};
}

} // namespace internal
} // namespace v8
