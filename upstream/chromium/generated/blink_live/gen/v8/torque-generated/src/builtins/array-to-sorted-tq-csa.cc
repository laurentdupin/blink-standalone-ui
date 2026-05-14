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
#include "torque-generated/src/builtins/array-to-sorted-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-to-sorted-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/third_party/v8/builtins/array-sort-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/array-to-sorted.tq?l=6&c=1
TNode<JSArray> CopyWorkArrayToNewFastJSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, ElementsKind p_elementsKind, TNode<Smi> p_numberOfNonUndefined) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, ((CodeStubAssembler(state_).ElementsKindEqual(p_elementsKind, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_SMI_ELEMENTS))) || (CodeStubAssembler(state_).ElementsKindEqual(p_elementsKind, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_ELEMENTS)))));
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-to-sorted.tq", 9});
      CodeStubAssembler(state_).FailAssert("Torque assert 'elementsKind == ElementsKind::PACKED_SMI_ELEMENTS || elementsKind == ElementsKind::PACKED_ELEMENTS' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp1;
  TNode<Smi> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<BoolT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp2 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp4 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp3});
    tmp5 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_numberOfNonUndefined}, TNode<Smi>{tmp4});
    tmp6 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp2}, TNode<Smi>{tmp5});
    ca_.Branch(tmp6, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-to-sorted.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'len == numberOfNonUndefined + sortState.number_of_undefined' failed", pos_stack);
    }
  }

  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, JSArray::kMaxFastArrayLength);
    tmp8 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp2}, TNode<Smi>{tmp7});
    ca_.Branch(tmp8, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-to-sorted.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'len <= kMaxFastArrayLength' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp9;
  TNode<FixedArrayBase> tmp10;
  TNode<FixedArray> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<FixedArray> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<BoolT> tmp20;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp2});
    tmp10 = CodeStubAssembler(state_).AllocateFixedArray(p_elementsKind, TNode<IntPtrT>{tmp9});
    tmp11 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp10});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp13 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp12});
    tmp14 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_numberOfNonUndefined});
    tmp15 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).CopyElements(p_elementsKind, TNode<FixedArrayBase>{tmp11}, TNode<IntPtrT>{tmp15}, TNode<FixedArrayBase>{tmp13}, TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp14});
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp18 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp17});
    tmp19 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp20 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp18}, TNode<Smi>{tmp19});
    ca_.Branch(tmp20, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp21;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp21 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block12, tmp21);
  }

  TNode<BoolT> tmp22;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp22 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ElementsKindEqual(p_elementsKind, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_ELEMENTS))));
    ca_.Goto(&block12, tmp22);
  }

  TNode<BoolT> phi_bb12_7;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_7);
    ca_.Branch(phi_bb12_7, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-to-sorted.tq", 25});
      CodeStubAssembler(state_).FailAssert("Torque assert 'sortState.number_of_undefined == 0 || elementsKind == ElementsKind::PACKED_ELEMENTS' failed", pos_stack);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block15, p_numberOfNonUndefined);
  }

  TNode<Smi> phi_bb15_6;
  TNode<BoolT> tmp23;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_6);
    tmp23 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb15_6}, TNode<Smi>{tmp2});
    ca_.Branch(tmp23, &block13, std::vector<compiler::Node*>{phi_bb15_6}, &block14, std::vector<compiler::Node*>{phi_bb15_6});
  }

  TNode<Smi> phi_bb13_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<UintPtrT> tmp28;
  TNode<UintPtrT> tmp29;
  TNode<BoolT> tmp30;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    std::tie(tmp24, tmp25, tmp26) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp11}).Flatten();
    tmp27 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb13_6});
    tmp28 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp27});
    tmp29 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp26});
    tmp30 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp28}, TNode<UintPtrT>{tmp29});
    ca_.Branch(tmp30, &block21, std::vector<compiler::Node*>{phi_bb13_6, phi_bb13_6, phi_bb13_6}, &block22, std::vector<compiler::Node*>{phi_bb13_6, phi_bb13_6, phi_bb13_6});
  }

  TNode<Smi> phi_bb21_6;
  TNode<Smi> phi_bb21_11;
  TNode<Smi> phi_bb21_12;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<Union<HeapObject, TaggedIndex>> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<Undefined> tmp35;
  TNode<Smi> tmp36;
  TNode<Smi> tmp37;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_6, &phi_bb21_11, &phi_bb21_12);
    tmp31 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp27});
    tmp32 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp31});
    std::tie(tmp33, tmp34) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp24}, TNode<IntPtrT>{tmp32}).Flatten();
    tmp35 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp33, tmp34}, tmp35);
    tmp36 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp37 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb21_6}, TNode<Smi>{tmp36});
    ca_.Goto(&block15, tmp37);
  }

  TNode<Smi> phi_bb22_6;
  TNode<Smi> phi_bb22_11;
  TNode<Smi> phi_bb22_12;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_6, &phi_bb22_11, &phi_bb22_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb14_6;
  TNode<NativeContext> tmp38;
  TNode<Map> tmp39;
  TNode<JSArray> tmp40;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_6);
    tmp38 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp39 = CodeStubAssembler(state_).LoadJSArrayElementsMap(p_elementsKind, TNode<NativeContext>{tmp38});
    tmp40 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp39}, TNode<FixedArrayBase>{tmp11});
    ca_.Goto(&block25);
  }

    ca_.Bind(&block25);
  return TNode<JSArray>{tmp40};
}

// https://crsrc.org/c/v8/src/builtins/array-to-sorted.tq?l=36&c=1
TNode<JSArray> CopyWorkArrayToNewJSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_numberOfNonUndefined) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp2});
    tmp4 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_numberOfNonUndefined}, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp1}, TNode<Smi>{tmp4});
    ca_.Branch(tmp5, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-to-sorted.tq", 40});
      CodeStubAssembler(state_).FailAssert("Torque assert 'len == numberOfNonUndefined + sortState.number_of_undefined' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<FixedArray> tmp7;
  TNode<JSArray> tmp8;
  TNode<Smi> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp7 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp6});
    tmp8 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{p_context}, TNode<Number>{tmp1});
    tmp9 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block6, tmp9);
  }

  TNode<Smi> phi_bb6_6;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_6);
    tmp10 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb6_6}, TNode<Smi>{p_numberOfNonUndefined});
    ca_.Branch(tmp10, &block4, std::vector<compiler::Node*>{phi_bb6_6}, &block5, std::vector<compiler::Node*>{phi_bb6_6});
  }

  TNode<Smi> phi_bb4_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<UintPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<BoolT> tmp17;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_6);
    std::tie(tmp11, tmp12, tmp13) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp7}).Flatten();
    tmp14 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb4_6});
    tmp15 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp14});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp13});
    tmp17 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp15}, TNode<UintPtrT>{tmp16});
    ca_.Branch(tmp17, &block12, std::vector<compiler::Node*>{phi_bb4_6, phi_bb4_6, phi_bb4_6, phi_bb4_6}, &block13, std::vector<compiler::Node*>{phi_bb4_6, phi_bb4_6, phi_bb4_6, phi_bb4_6});
  }

  TNode<Smi> phi_bb12_6;
  TNode<Smi> phi_bb12_8;
  TNode<Smi> phi_bb12_13;
  TNode<Smi> phi_bb12_14;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Union<HeapObject, TaggedIndex>> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Object> tmp22;
  TNode<JSAny> tmp23;
  TNode<JSAny> tmp24;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_6, &phi_bb12_8, &phi_bb12_13, &phi_bb12_14);
    tmp18 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp14});
    tmp19 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp18});
    std::tie(tmp20, tmp21) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp11}, TNode<IntPtrT>{tmp19}).Flatten();
    tmp22 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp20, tmp21});
    tmp23 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp22});
    tmp24 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, p_context, tmp8, phi_bb12_8, tmp23);
    tmp25 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp26 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb12_6}, TNode<Smi>{tmp25});
    ca_.Goto(&block6, tmp26);
  }

  TNode<Smi> phi_bb13_6;
  TNode<Smi> phi_bb13_8;
  TNode<Smi> phi_bb13_13;
  TNode<Smi> phi_bb13_14;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6, &phi_bb13_8, &phi_bb13_13, &phi_bb13_14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb5_6;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_6);
    ca_.Goto(&block18, phi_bb5_6);
  }

  TNode<Smi> phi_bb18_6;
  TNode<BoolT> tmp27;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_6);
    tmp27 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb18_6}, TNode<Smi>{tmp1});
    ca_.Branch(tmp27, &block16, std::vector<compiler::Node*>{phi_bb18_6}, &block17, std::vector<compiler::Node*>{phi_bb18_6});
  }

  TNode<Smi> phi_bb16_6;
  TNode<Undefined> tmp28;
  TNode<JSAny> tmp29;
  TNode<Smi> tmp30;
  TNode<Smi> tmp31;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_6);
    tmp28 = Undefined_0(state_);
    tmp29 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, p_context, tmp8, phi_bb16_6, tmp28);
    tmp30 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp31 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb16_6}, TNode<Smi>{tmp30});
    ca_.Goto(&block18, tmp31);
  }

  TNode<Smi> phi_bb17_6;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_6);
    ca_.Goto(&block20);
  }

    ca_.Bind(&block20);
  return TNode<JSArray>{tmp8};
}

TF_BUILTIN(ArrayPowerSortIntoCopy, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CompactReceiverElementsIntoWorkArray_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, true);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, JSArray::kMaxInlineSortLength);
    tmp2 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp0}, TNode<Smi>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    BinaryInsertionSort_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp3}, TNode<Smi>{tmp4}, TNode<Smi>{tmp0});
    ca_.Goto(&block3);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ArrayPowerSortImpl_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp0});
    ca_.Goto(&block3);
  }

  TNode<IntPtrT> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp6 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp5});
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, JSArray::kMaxFastArrayLength);
    tmp8 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp6}, TNode<Smi>{tmp7});
    ca_.Branch(tmp8, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp9;
  TNode<Smi> tmp10;
  TNode<Smi> tmp11;
  TNode<BoolT> tmp12;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp10 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp9});
    tmp11 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp12 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp10}, TNode<Smi>{tmp11});
    ca_.Branch(tmp12, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block7);
  }

  TNode<IntPtrT> tmp13;
  TNode<FixedArray> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<BoolT> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp14 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp13});
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp0});
    tmp16 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp14});
    tmp17 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp16});
    ca_.Branch(tmp17, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-to-sorted.tq", 70});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Convert<intptr>(numberOfNonUndefined) <= workArray.length_intptr' failed", pos_stack);
    }
  }

  TNode<Smi> tmp18;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp18 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block14, tmp18);
  }

  TNode<Smi> phi_bb14_4;
  TNode<BoolT> tmp19;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_4);
    tmp19 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb14_4}, TNode<Smi>{tmp0});
    ca_.Branch(tmp19, &block12, std::vector<compiler::Node*>{phi_bb14_4}, &block13, std::vector<compiler::Node*>{phi_bb14_4});
  }

  TNode<Smi> phi_bb12_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<UintPtrT> tmp24;
  TNode<UintPtrT> tmp25;
  TNode<BoolT> tmp26;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_4);
    std::tie(tmp20, tmp21, tmp22) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp23 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb12_4});
    tmp24 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp23});
    tmp25 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp22});
    tmp26 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp24}, TNode<UintPtrT>{tmp25});
    ca_.Branch(tmp26, &block20, std::vector<compiler::Node*>{phi_bb12_4, phi_bb12_4, phi_bb12_4}, &block21, std::vector<compiler::Node*>{phi_bb12_4, phi_bb12_4, phi_bb12_4});
  }

  TNode<Smi> phi_bb20_4;
  TNode<Smi> phi_bb20_9;
  TNode<Smi> phi_bb20_10;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Union<HeapObject, TaggedIndex>> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Object> tmp31;
  TNode<JSAny> tmp32;
  TNode<BoolT> tmp33;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_4, &phi_bb20_9, &phi_bb20_10);
    tmp27 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp23});
    tmp28 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp27});
    std::tie(tmp29, tmp30) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp20}, TNode<IntPtrT>{tmp28}).Flatten();
    tmp31 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp29, tmp30});
    tmp32 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp31});
    tmp33 = CodeStubAssembler(state_).TaggedIsNotSmi(TNode<Object>{tmp32});
    ca_.Branch(tmp33, &block24, std::vector<compiler::Node*>{phi_bb20_4}, &block25, std::vector<compiler::Node*>{phi_bb20_4});
  }

  TNode<Smi> phi_bb21_4;
  TNode<Smi> phi_bb21_9;
  TNode<Smi> phi_bb21_10;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_4, &phi_bb21_9, &phi_bb21_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb24_4;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_4);
    ca_.Goto(&block7);
  }

  TNode<Smi> phi_bb25_4;
  TNode<Smi> tmp34;
  TNode<Smi> tmp35;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_4);
    tmp34 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp35 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb25_4}, TNode<Smi>{tmp34});
    ca_.Goto(&block14, tmp35);
  }

  TNode<Smi> phi_bb13_4;
  TNode<JSArray> tmp36;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_4);
    tmp36 = CopyWorkArrayToNewFastJSArray_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_SMI_ELEMENTS), TNode<Smi>{tmp0});
    CodeStubAssembler(state_).Return(tmp36);
  }

  TNode<JSArray> tmp37;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp37 = CopyWorkArrayToNewFastJSArray_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_ELEMENTS), TNode<Smi>{tmp0});
    CodeStubAssembler(state_).Return(tmp37);
  }

  TNode<JSArray> tmp38;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp38 = CopyWorkArrayToNewJSArray_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp0});
    CodeStubAssembler(state_).Return(tmp38);
  }
}

TF_BUILTIN(ArrayPrototypeToSorted, CodeStubAssembler) {
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
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kArrayByCopy));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Undefined_OR_JSFunction_OR_CallableApiObject_OR_CallableJSProxy_OR_JSWrappedFunction_OR_JSBoundFunction_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, &label3);
    ca_.Goto(&block3);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kBadSortComparisonFunction), TNode<Object>{tmp1});
  }

  TNode<JSReceiver> tmp4;
  TNode<Number> tmp5;
  TNode<Number> tmp6;
  TNode<BoolT> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = ca_.CallBuiltin<JSReceiver>(Builtin::kToObject, parameter0, parameter1);
    tmp5 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp4});
    tmp6 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = IsNumberEqual_0(state_, TNode<Number>{tmp5}, TNode<Number>{tmp6});
    ca_.Branch(tmp7, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<Number> tmp8;
  TNode<JSArray> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp8 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp9 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{parameter0}, TNode<Number>{tmp8});
    arguments.PopAndReturn(tmp9);
  }

  TNode<Number> tmp10;
  TNode<BoolT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp11 = IsNumberEqual_0(state_, TNode<Number>{tmp5}, TNode<Number>{tmp10});
    ca_.Branch(tmp11, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<Number> tmp12;
  TNode<JSArray> tmp13;
  TNode<Smi> tmp14;
  TNode<JSAny> tmp15;
  TNode<JSAny> tmp16;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp13 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{parameter0}, TNode<Number>{tmp12});
    tmp14 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp4}, TNode<JSAny>{tmp14});
    tmp16 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, parameter0, tmp13, tmp14, tmp15);
    arguments.PopAndReturn(tmp13);
  }

  TNode<Number> tmp17;
  TNode<BoolT> tmp18;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp17 = FromConstexpr_Number_constexpr_uint32_0(state_, JSArray::kMaxArrayLength);
    tmp18 = NumberIsGreaterThan_0(state_, TNode<Number>{tmp5}, TNode<Number>{tmp17});
    ca_.Branch(tmp18, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).ThrowRangeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidArrayLength), TNode<Object>{tmp5});
  }

  TNode<SortState> tmp19;
  TNode<JSArray> tmp20;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp19 = NewSortState_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp4}, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>{tmp2}, TNode<Number>{tmp5}, true);
    tmp20 = ca_.CallBuiltin<JSArray>(Builtin::kArrayPowerSortIntoCopy, parameter0, tmp19);
    arguments.PopAndReturn(tmp20);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-to-sorted.tq?l=97&c=21
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> Cast_Undefined_OR_JSFunction_OR_CallableApiObject_OR_CallableJSProxy_OR_JSWrappedFunction_OR_JSBoundFunction_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Undefined_OR_JSFunction_OR_CallableApiObject_OR_CallableJSProxy_OR_JSWrappedFunction_OR_JSBoundFunction_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>{tmp2};
}

} // namespace internal
} // namespace v8
